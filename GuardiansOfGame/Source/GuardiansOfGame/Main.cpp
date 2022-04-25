// Fill out your copyright notice in the Description page of Project Settings.

#include "Main.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

#include "MainController.h"
#include "MainAnimInstance.h"
#include "MainStatComponent.h"
#include "OcclusionChecker.h"
#include "ParkourLineTracer.h"
#include "QuestNPC.h"

// Sets default values
AMain::AMain()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->bHiddenInGame = false;
	GetCapsuleComponent()->SetCapsuleHalfHeight(90.0f);

	BaseTurnRate = 45.0f;
	BaseLookUpRate = 45.0f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->SetRelativeRotation(FRotator(-25.0f, 0.0f, 0.0f));
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->CameraLagSpeed = 20.0f;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MainMesh(TEXT("SkeletalMesh'/Game/Character/ybot/ybot.ybot'"));
	if(MainMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MainMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -93.0f), FRotator(0.0f, -90.0f, 0.0f));
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> MainAnimInstance(TEXT("AnimBlueprint'/Game/Character/Animation/MainAnimInstance_BP.MainAnimInstance_BP_C'"));
	if(MainAnimInstance.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(MainAnimInstance.Class);
	}

	InteractionStatus = EInteractionStatus::EIS_Normal;
	MovementStatus = EMovementStatus::EMS_Normal;

	MainStat = CreateDefaultSubobject<UMainStatComponent>(TEXT("MainStat"));

	InteractingNPC = nullptr;

	bIsBattling = false;
	bIsRolling = false;

	TargetPosition = FVector(0.0f);

	RollingInterpSpeed = 1.2f;
	SlidingInterpSpeed = 2.5f;
	LagSpeedInterpSpeed = 2.5f;

	ParkourLineTracer = CreateDefaultSubobject<UParkourLineTracer>(TEXT("ParkourLineTracer"));

	OcclusionChecker = CreateDefaultSubobject<UOcclusionChecker>(TEXT("OcclusionChecker"));
}

// Called when the game starts or when spawned
void AMain::BeginPlay()
{
	Super::BeginPlay();

	MainController = Cast<AMainController>(Controller);
	MainAnim = Cast<UMainAnimInstance>(GetMesh()->GetAnimInstance());
}

// Called every frame
void AMain::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsRolling)
	{
		const FVector InterpLocation = FMath::VInterpTo(GetActorLocation(), TargetPosition, DeltaTime, RollingInterpSpeed);
		SetActorLocation(InterpLocation);
	}

	if (!bIsRolling && CameraBoom->CameraLagSpeed < 20.0f)
	{
		const float InterpLagSpeed = FMath::FInterpTo(CameraBoom->CameraLagSpeed, 20.0f, DeltaTime, LagSpeedInterpSpeed);
		CameraBoom->CameraLagSpeed = InterpLagSpeed;
	}

	if (bIsSliding)
	{
		const FVector InterpLocation = FMath::VInterpTo(GetActorLocation(), TargetPosition, DeltaTime, SlidingInterpSpeed);
		SetActorLocation(InterpLocation);
	}
}

// Called to bind functionality to input
void AMain::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Interaction", IE_Pressed, this, &AMain::Interaction);

	PlayerInputComponent->BindAction("JumpOrRoll", IE_Pressed, this, &AMain::SpaceDown);
	PlayerInputComponent->BindAction("JumpOrRoll", IE_Released, this, &AMain::SpaceUp);

	PlayerInputComponent->BindAction("ParkourActions", IE_Pressed, this, &AMain::LCtrlDown);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMain::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMain::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AMain::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &AMain::LookUp);
}

void AMain::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AMain::MoveForward(const float Value)
{
	if (Controller && Value)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AMain::MoveRight(const float Value)
{
	if (Controller && Value)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void AMain::Turn(const float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AMain::LookUp(const float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AMain::Interaction()
{
	switch (InteractionStatus)
	{
	case EInteractionStatus::EIS_TalkWithNPC:
		if(MainController && InteractingNPC)
		{
			UIOff();

			const AQuestNPC* QuestNPC = Cast<AQuestNPC>(InteractingNPC);
			if(QuestNPC)
			{
				DisableInput(MainController);
				MainController->BeginChat(QuestNPC->GetCurDialogue(), QuestNPC->GetUIName());
			}
		}
		break;

	case EInteractionStatus::EIS_PickUpItem:
		// TODO: 아이템 획득 기능 추가하기
		UE_LOG(LogTemp, Warning, TEXT("EIS_PickUpItem"));
		break;

	default:
		break;
	}
}

void AMain::SpaceDown()
{
	if (bIsBattling)
	{
		if(bIsRolling)
		{
			return;
		}

		TargetPosition = GetActorLocation() + GetActorForwardVector() * 500.0f;
		bIsRolling = true;

		MainAnim->PlayRollMontage();
	}
	else
	{
		Super::Jump();
	}
}

void AMain::SpaceUp()
{
	if(!bIsBattling)
	{
		Super::StopJumping();
	}
}

void AMain::LCtrlDown()
{
	if (MovementStatus == EMovementStatus::EMS_Parkour)
	{
		return;
	}

	ParkourLineTracer->CheckObstacle(this);
}

void AMain::UIOn() const
{
	if(InteractingNPC)
	{
		InteractingNPC->GetKeyWidgetComponent()->SetVisibility(true);
	}
}

void AMain::UIOff() const
{
	if (InteractingNPC)
	{
		InteractingNPC->GetKeyWidgetComponent()->SetVisibility(false);
	}
}

void AMain::SetQuestProgress()
{
	UIOn();
	EnableInput(MainController);

	AQuestNPC* QuestNPC = Cast<AQuestNPC>(InteractingNPC);
	int CurQuestNum = MainStat->GetCurQuestNum();

	switch (CurQuestNum)
	{
	case 0:
		if (MainStat->GetQuestProgress().CurQuestSuccess)
		{
			MainStat->SetCurQuestAccept(false);
			MainStat->SetCurQuestSuccess(false);

			QuestNPC->SetCurDialogue(QuestNPC->GetQuestDialogue(CurQuestNum).Success);

			MainStat->SetCurQuestNum(++CurQuestNum);
		}
		else
		{
			MainStat->SetCurQuestAccept(true);
			MainStat->SetQuestAcceptArr(CurQuestNum, true);

			QuestNPC->SetCurDialogue(QuestNPC->GetQuestDialogue(CurQuestNum).Handle);
		}
		break;
	case 1:
		if (MainStat->GetQuestProgress().CurQuestAccept)
		{
			if (MainStat->GetQuestProgress().CurQuestSuccess)
			{
				QuestNPC->SetCurDialogue(QuestNPC->GetQuestDialogue(CurQuestNum).Success);
			}
			else
			{
				MainStat->SetQuestAcceptArr(CurQuestNum, true);
				QuestNPC->SetCurDialogue(QuestNPC->GetQuestDialogue(CurQuestNum).Handle);
			}
		}
		else
		{
			MainStat->SetCurQuestAccept(true);
			QuestNPC->SetCurDialogue(QuestNPC->GetQuestDialogue(CurQuestNum).Give);
		}
		break;
	default:
		break;
	}
}

void AMain::SwitchLevel(const FName LevelName) const
{
	FString CurLevelName = GetWorld()->GetMapName();
	CurLevelName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);

	MainStat->Save();

	UGameplayStatics::OpenLevel(GetWorld(), FName(LevelName));
}