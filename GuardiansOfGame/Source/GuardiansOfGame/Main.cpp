// Fill out your copyright notice in the Description page of Project Settings.

#include "Main.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "MainController.h"
#include "MainAnimInstance.h"
#include "NPC.h"

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
}

void AMain::SpaceUp()
{
}

void AMain::LCtrlDown()
{
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

void AMain::SetProgressQuest()
{
}