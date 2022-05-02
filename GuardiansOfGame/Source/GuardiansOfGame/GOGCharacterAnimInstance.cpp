// Fill out your copyright notice in the Description page of Project Settings.

#include "GOGCharacterAnimInstance.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "GOGCharacter.h"
#include "Weapon.h"

UGOGCharacterAnimInstance::UGOGCharacterAnimInstance()
{
	GOGCharacter = nullptr;

	Speed = 0.0f;
	bIsInAir = false;
	bWeaponEquipped = false;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> RollMontageAsset(TEXT("AnimMontage'/Game/WizardCharacter/Character/Animations/Parkour/Roll_Montage.Roll_Montage'"));
	if (RollMontageAsset.Succeeded())
	{
		RollMontage = RollMontageAsset.Object;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NotExist"));
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> VaultMontageAsset(TEXT("AnimMontage'/Game/WizardCharacter/Character/Animations/Parkour/Vault_Over_Box_Montage.Vault_Over_Box_Montage'"));
	if (VaultMontageAsset.Succeeded())
	{
		VaultMontage = VaultMontageAsset.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ClimbMontageAsset(TEXT("AnimMontage'/Game/WizardCharacter/Character/Animations/Parkour/Climb_Jump_Montage.Climb_Jump_Montage'"));
	if (ClimbMontageAsset.Succeeded())
	{
		ClimbMontage = ClimbMontageAsset.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> SlideMontageAsset(TEXT("AnimMontage'/Game/WizardCharacter/Character/Animations/Parkour/Slide_Montage.Slide_Montage'"));
	if (SlideMontageAsset.Succeeded())
	{
		SlideMontage = SlideMontageAsset.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> EquipMontageAsset(TEXT("AnimMontage'/Game/WizardCharacter/Character/Animations/Combat/Equip_Montage.Equip_Montage'"));
	if (EquipMontageAsset.Succeeded())
	{
		EquipMontage = EquipMontageAsset.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> UnequipMontageAsset(TEXT("AnimMontage'/Game/WizardCharacter/Character/Animations/Combat/Disequip_Montage.Disequip_Montage'"));
	if (UnequipMontageAsset.Succeeded())
	{
		UnequipMontage = UnequipMontageAsset.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> AttackMontageAsset(TEXT("AnimMontage'/Game/WizardCharacter/Character/Animations/Combat/AttackMontage.AttackMontage'"));
	if (AttackMontageAsset.Succeeded())
	{
		AttackMontage = AttackMontageAsset.Object;
	}
}

void UGOGCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	GOGCharacter = Cast<AGOGCharacter>(TryGetPawnOwner());
}

void UGOGCharacterAnimInstance::NativeUpdateAnimation(const float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (GOGCharacter)
	{
		Speed = GOGCharacter->GetVelocity().Size2D();
		bIsInAir = GOGCharacter->GetMovementComponent()->IsFalling();
	}
}

void UGOGCharacterAnimInstance::PlayRollMontage()
{
	Montage_Play(RollMontage);
}

void UGOGCharacterAnimInstance::PlayVaultMontage(const float ObstacleHeight, const float Left, const float Right)
{
	GOGCharacter->SetMovementStatus(EMovementStatus::EMS_Parkour);

	GOGCharacter->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GOGCharacter->GetCharacterMovement()->SetMovementMode(MOVE_Flying);

	FVector Location = GOGCharacter->GetActorLocation();
	Location.Z += ObstacleHeight;
	GOGCharacter->SetActorLocation(Location);

	FTimerHandle WaitVaultHandle;

	// TODO: 애니메이션 몽타주 (왼쪽 손 : 오른쪽 손) 으로 변경하기
	const float WaitTime = Left > Right ? Montage_Play(VaultMontage) : Montage_Play(VaultMontage);

	GetWorld()->GetTimerManager().SetTimer(WaitVaultHandle, FTimerDelegate::CreateLambda([&]() {
		if (GOGCharacter)
		{
			GOGCharacter->SetMovementStatus(EMovementStatus::EMS_Normal);
		}
	}), WaitTime, false);
}

void UGOGCharacterAnimInstance::PlayClimbMontage(const float ObstacleHeight)
{
	GOGCharacter->SetMovementStatus(EMovementStatus::EMS_Parkour);

	GOGCharacter->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GOGCharacter->GetCharacterMovement()->SetMovementMode(MOVE_Flying);

	FVector Location = GOGCharacter->GetActorLocation();
	Location.Z += ObstacleHeight;
	GOGCharacter->SetActorLocation(Location);

	FTimerHandle WaitClimbHandle;
	const float WaitTime = Montage_Play(ClimbMontage);

	GetWorld()->GetTimerManager().SetTimer(WaitClimbHandle, FTimerDelegate::CreateLambda([&]() {
		if (GOGCharacter)
		{
			GOGCharacter->SetMovementStatus(EMovementStatus::EMS_Normal);

			GOGCharacter->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			GOGCharacter->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
		}
	}), WaitTime, false);
}

void UGOGCharacterAnimInstance::PlaySlideMontage(const FVector TargetPosition)
{
	GOGCharacter->SetMovementStatus(EMovementStatus::EMS_Parkour);
	GOGCharacter->SetTargetPosition(TargetPosition);
	GOGCharacter->SetIsSliding(true);

	GOGCharacter->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	FTimerHandle WaitSlideHandle;
	const float WaitTime = Montage_Play(SlideMontage);

	GetWorld()->GetTimerManager().SetTimer(WaitSlideHandle, FTimerDelegate::CreateLambda([&]() {
		if (GOGCharacter)
		{
			GOGCharacter->SetMovementStatus(EMovementStatus::EMS_Normal);
			GOGCharacter->SetIsSliding(false);

			GOGCharacter->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			GOGCharacter->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
		}
	}), WaitTime, false);
}

void UGOGCharacterAnimInstance::PlayEquipMontage()
{
	Montage_Play(EquipMontage);
}

void UGOGCharacterAnimInstance::PlayUnEquipMontage()
{
	Montage_Play(UnequipMontage);
}

void UGOGCharacterAnimInstance::PlayAttackMontage()
{
	Montage_Play(AttackMontage);
}

void UGOGCharacterAnimInstance::AnimNotify_RollStart() const
{
	GOGCharacter->SetIsRolling(true);

	GOGCharacter->GetCameraBoom()->CameraLagSpeed = 5.0f;
}

void UGOGCharacterAnimInstance::AnimNotify_RollEnd() const
{
	GOGCharacter->SetIsRolling(false);
}

void UGOGCharacterAnimInstance::AnimNotify_VaultEnd() const
{
	GOGCharacter->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GOGCharacter->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
}

void UGOGCharacterAnimInstance::AnimNotify_Equip()
{
	bWeaponEquipped = true;

	GOGCharacter->SetWeaponEquipped(true);
	GOGCharacter->GetWeapon()->EquipToHand(GOGCharacter);
}

void UGOGCharacterAnimInstance::AnimNotify_Unequip()
{
	bWeaponEquipped = false;

	GOGCharacter->SetWeaponEquipped(false);
	GOGCharacter->GetWeapon()->EquipToBack(GOGCharacter);
}