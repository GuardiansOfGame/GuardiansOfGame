// Fill out your copyright notice in the Description page of Project Settings.

#include "GOGCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

#include "GOGCharacterAnimInstance.h"
#include "GOGCharacterController.h"
#include "GOGCharacterStatComponent.h"
#include "OcclusionChecker.h"
#include "ParkourLineTracer.h"
#include "QuestNPC.h"
#include "Weapon.h"

// Sets default values
AGOGCharacter::AGOGCharacter()
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
	GetCharacterMovement()->GravityScale = 1.2f;

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

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MainMesh(TEXT("SkeletalMesh'/Game/WizardCharacter/Character/Mesh/Wizard_Sk.Wizard_Sk'"));
	if (MainMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MainMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -93.0f), FRotator(0.0f, -90.0f, 0.0f));
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> GOGAnimInstanceAsset(TEXT("AnimBlueprint'/Game/WizardCharacter/Character/Animations/GOGAnimInstance_BP.GOGAnimInstance_BP_C'"));
	if (GOGAnimInstanceAsset.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(GOGAnimInstanceAsset.Class);
	}

	InteractionStatus = EInteractionStatus::EIS_Normal;
	MovementStatus = EMovementStatus::EMS_Normal;

	Stat = CreateDefaultSubobject<UGOGCharacterStatComponent>(TEXT("Stat"));

	InteractingNPC = nullptr;

	RunningSpeed = 650.0f;
	SprintingSpeed = 950.0f;

	GetCharacterMovement()->MaxWalkSpeed = RunningSpeed;

	bIsBattling = false;
	bIsRolling = false;
	bShiftKeyDown = false;

	TargetPosition = FVector(0.0f);

	RollingInterpSpeed = 1.5f;
	SlidingInterpSpeed = 2.5f;
	LagSpeedInterpSpeed = 2.5f;

	ParkourLineTracer = CreateDefaultSubobject<UParkourLineTracer>(TEXT("ParkourLineTracer"));

	OcclusionChecker = CreateDefaultSubobject<UOcclusionChecker>(TEXT("OcclusionChecker"));

	bWeaponEquipped = false;
	bIsAttacking = false;

	EndComboAttack();
	MaxComboNum = 3;

	MaxHealth = 100.0f;
	CurrentHealth = MaxHealth;

	MaxStamina = 100.0f;
	CurrentStamina = MaxStamina;

	StaminaDrainRate = 15.0f;
	MinSprintStamina = 30.0f;
}

// Called when the game starts or when spawned
void AGOGCharacter::BeginPlay()
{
	Super::BeginPlay();

	GOGController = Cast<AGOGCharacterController>(Controller);
	AnimInstance = Cast<UGOGCharacterAnimInstance>(GetMesh()->GetAnimInstance());

	AnimInstance->OnMontageEnded.AddDynamic(this, &AGOGCharacter::OnMontageEnded);

	Weapon = GetWorld()->SpawnActor<AWeapon>();
	if (Weapon)
	{
		Weapon->EquipToBack(this);
	}
}

// Called every frame
void AGOGCharacter::Tick(const float DeltaTime)
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
void AGOGCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Interaction", IE_Pressed, this, &AGOGCharacter::Interaction);

	PlayerInputComponent->BindAction("JumpOrRoll", IE_Pressed, this, &AGOGCharacter::SpaceDown);
	PlayerInputComponent->BindAction("JumpOrRoll", IE_Released, this, &AGOGCharacter::SpaceUp);

	PlayerInputComponent->BindAction("ParkourActions", IE_Pressed, this, &AGOGCharacter::LCtrlDown);

	PlayerInputComponent->BindAction("Equip", IE_Pressed, this, &AGOGCharacter::Equip);

	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AGOGCharacter::Attack);

	PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &AGOGCharacter::Pause);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AGOGCharacter::ShiftKeyDown);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AGOGCharacter::ShiftKeyUp);

	PlayerInputComponent->BindAxis("MoveForward", this, &AGOGCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AGOGCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AGOGCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &AGOGCharacter::LookUp);
}

void AGOGCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AGOGCharacter::MoveForward(const float Value)
{
	if (CanMove(Value))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AGOGCharacter::MoveRight(const float Value)
{
	if (CanMove(Value))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void AGOGCharacter::Turn(const float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AGOGCharacter::LookUp(const float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AGOGCharacter::Interaction()
{
	switch (InteractionStatus)
	{
	case EInteractionStatus::EIS_TalkWithNPC:
		if (GOGController && InteractingNPC)
		{
			UIOff();

			const AQuestNPC* QuestNPC = Cast<AQuestNPC>(InteractingNPC);
			if (QuestNPC)
			{
				DisableInput(GOGController);
				GOGController->BeginChat(QuestNPC->GetCurDialogue(), QuestNPC->GetUIName());
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

void AGOGCharacter::SpaceDown()
{
	if (bIsBattling)
	{
		if (bIsRolling || bIsAttacking)
		{
			return;
		}

		TargetPosition = GetActorLocation() + GetActorForwardVector() * 500.0f;
		bIsRolling = true;

		AnimInstance->PlayRollMontage();
	}
	else
	{
		if(!bIsAttacking)
		{
			Super::Jump();
		}
	}
}

void AGOGCharacter::SpaceUp()
{
	if (!bIsBattling)
	{
		Super::StopJumping();
	}
}

void AGOGCharacter::LCtrlDown()
{
	if (MovementStatus == EMovementStatus::EMS_Parkour || bIsAttacking)
	{
		return;
	}

	ParkourLineTracer->CheckObstacle(this);
}

void AGOGCharacter::Equip()
{
	// Z Key
	bWeaponEquipped ? AnimInstance->PlayUnEquipMontage() : AnimInstance->PlayEquipMontage();
}

void AGOGCharacter::Attack()
{
	// Left Mouse Button
	if (!bWeaponEquipped)
	{
		AnimInstance->PlayEquipMontage();
		return;
	}

	if(bIsAttacking)
	{
		if(bCanNextCombo)
		{
			bIsComboInputOn = true;
		}
	}
	else
	{
		StartComboAttack();

		bIsAttacking = true;
		AnimInstance->PlayAttackMontage();
	}
}

void AGOGCharacter::Pause()
{
	if(GOGController)
	{
		GOGController->TogglePause(true);
	}
}

void AGOGCharacter::ShiftKeyDown()
{
	bShiftKeyDown = true;
}

void AGOGCharacter::ShiftKeyUp()
{
	bShiftKeyDown = false;
}

void AGOGCharacter::SetMovementStatus(const EMovementStatus Status)
{
	MovementStatus = Status;

	if(MovementStatus == EMovementStatus::EMS_Sprinting)
	{
		GetCharacterMovement()->MaxWalkSpeed = SprintingSpeed;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = RunningSpeed;
	}
}

void AGOGCharacter::UIOn() const
{
	if (InteractingNPC)
	{
		InteractingNPC->GetKeyWidgetComponent()->SetVisibility(true);
	}
}

void AGOGCharacter::UIOff() const
{
	if (InteractingNPC)
	{
		InteractingNPC->GetKeyWidgetComponent()->SetVisibility(false);
	}
}

bool AGOGCharacter::CanMove(const float Value) const
{
	if(GOGController)
	{
		return Value
			   && !bIsAttacking;
	}

	return false;
}

void AGOGCharacter::SetQuestProgress()
{
	UIOn();
	EnableInput(GOGController);

	AQuestNPC* QuestNPC = Cast<AQuestNPC>(InteractingNPC);
	int CurQuestNum = Stat->GetCurQuestNum();

	switch (CurQuestNum)
	{
	case 0:
		if (Stat->GetQuestProgress().CurQuestSuccess)
		{
			Stat->SetCurQuestAccept(false);
			Stat->SetCurQuestSuccess(false);

			QuestNPC->SetCurDialogue(QuestNPC->GetQuestDialogue(CurQuestNum).Success);

			Stat->SetCurQuestNum(++CurQuestNum);
		}
		else
		{
			Stat->SetCurQuestAccept(true);
			Stat->SetQuestAcceptArr(CurQuestNum, true);

			QuestNPC->SetCurDialogue(QuestNPC->GetQuestDialogue(CurQuestNum).Handle);
		}
		break;
	case 1:
		if (Stat->GetQuestProgress().CurQuestAccept)
		{
			if (Stat->GetQuestProgress().CurQuestSuccess)
			{
				QuestNPC->SetCurDialogue(QuestNPC->GetQuestDialogue(CurQuestNum).Success);
			}
			else
			{
				Stat->SetQuestAcceptArr(CurQuestNum, true);
				QuestNPC->SetCurDialogue(QuestNPC->GetQuestDialogue(CurQuestNum).Handle);
			}
		}
		else
		{
			Stat->SetCurQuestAccept(true);
			QuestNPC->SetCurDialogue(QuestNPC->GetQuestDialogue(CurQuestNum).Give);
		}
		break;
	default:
		break;
	}
}

void AGOGCharacter::SwitchLevel(const FName LevelName) const
{
	FString CurLevelName = GetWorld()->GetMapName();
	CurLevelName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);

	Stat->Save();

	UGameplayStatics::OpenLevel(GetWorld(), FName(LevelName));
}

void AGOGCharacter::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if(Montage == AnimInstance->GetClimbMontage())
	{
		MovementStatus = EMovementStatus::EMS_Normal;

		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	}
	else if(Montage == AnimInstance->GetSlideMontage())
	{
		MovementStatus = EMovementStatus::EMS_Normal;
		bIsSliding = false;

		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	}
	else if(Montage == AnimInstance->GetAttackMontage())
	{
		bIsAttacking = false;
		EndComboAttack();
	}
}

void AGOGCharacter::StartComboAttack()
{
	bCanNextCombo = true;
	bIsComboInputOn = false;

	CurrentComboNum = FMath::Clamp(CurrentComboNum + 1, 1, MaxComboNum);
}

void AGOGCharacter::EndComboAttack()
{
	bCanNextCombo = false;
	bIsComboInputOn = false;

	CurrentComboNum = 0;
}