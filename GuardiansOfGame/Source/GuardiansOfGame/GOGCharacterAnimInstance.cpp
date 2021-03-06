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
	MovementStatus = EMovementStatus::EMS_Normal;

	bWeaponEquipped = false;

	VaultHeight = 30.0f;
	InAirVaultHeight = 65.0f;
	InAirVaultForwardRate = 0.225f;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> RollMontageAsset(TEXT("AnimMontage'/Game/CustomContent/CharacterAnimations/Parkour/Roll_Montage.Roll_Montage'"));
	if (RollMontageAsset.Succeeded())
	{
		RollMontage = RollMontageAsset.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> LeftVaultMontageAsset(TEXT("AnimMontage'/Game/CustomContent/CharacterAnimations/Parkour/Vault_Hand_Left_Montage.Vault_Hand_Left_Montage'"));
	if (LeftVaultMontageAsset.Succeeded())
	{
		LeftVaultMontage = LeftVaultMontageAsset.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> RightVaultMontageAsset(TEXT("AnimMontage'/Game/CustomContent/CharacterAnimations/Parkour/Vault_Hand_Right_Montage.Vault_Hand_Right_Montage'"));
	if (RightVaultMontageAsset.Succeeded())
	{
		RightVaultMontage = RightVaultMontageAsset.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> NoHandVaultMontageAsset(TEXT("AnimMontage'/Game/CustomContent/CharacterAnimations/Parkour/Vault_Hand_No_Montage.Vault_Hand_No_Montage'"));
	if (NoHandVaultMontageAsset.Succeeded())
	{
		NoHandVaultMontage = NoHandVaultMontageAsset.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> InAirVaultMontageAsset(TEXT("AnimMontage'/Game/CustomContent/CharacterAnimations/Parkour/InAir_Vault_Montage.InAir_Vault_Montage'"));
	if (InAirVaultMontageAsset.Succeeded())
	{
		InAirVaultMontage = InAirVaultMontageAsset.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ClimbMontageAsset(TEXT("AnimMontage'/Game/CustomContent/CharacterAnimations/Parkour/Climb_Jump_Montage.Climb_Jump_Montage'"));
	if (ClimbMontageAsset.Succeeded())
	{
		ClimbMontage = ClimbMontageAsset.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> InAirClimbMontageAsset(TEXT("AnimMontage'/Game/CustomContent/CharacterAnimations/Parkour/InAir_Climb_Montage.InAir_Climb_Montage'"));
	if (InAirClimbMontageAsset.Succeeded())
	{
		InAirClimbMontage = InAirClimbMontageAsset.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> SlideMontageAsset(TEXT("AnimMontage'/Game/CustomContent/CharacterAnimations/Parkour/Slide_Montage.Slide_Montage'"));
	if (SlideMontageAsset.Succeeded())
	{
		SlideMontage = SlideMontageAsset.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> EquipMontageAsset(TEXT("AnimMontage'/Game/CustomContent/CharacterAnimations/Combat/Equip_Montage.Equip_Montage'"));
	if (EquipMontageAsset.Succeeded())
	{
		EquipMontage = EquipMontageAsset.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> UnequipMontageAsset(TEXT("AnimMontage'/Game/CustomContent/CharacterAnimations/Combat/Disequip_Montage.Disequip_Montage'"));
	if (UnequipMontageAsset.Succeeded())
	{
		UnequipMontage = UnequipMontageAsset.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> AttackMontageAsset(TEXT("AnimMontage'/Game/CustomContent/CharacterAnimations/Combat/AttackMontage.AttackMontage'"));
	if (AttackMontageAsset.Succeeded())
	{
		AttackMontage = AttackMontageAsset.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> DeathMontageAsset(TEXT("AnimMontage'/Game/CustomContent/CharacterAnimations/Combat/Death_Montage.Death_Montage'"));
	if (DeathMontageAsset.Succeeded())
	{
		DeathMontage = DeathMontageAsset.Object;
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
		MovementStatus = GOGCharacter->GetMovementStatus();
	}
}

void UGOGCharacterAnimInstance::PlayRollMontage()
{
	GOGCharacter->SetMovementStatus(EMovementStatus::EMS_Parkour);

	GOGCharacter->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GOGCharacter->GetCharacterMovement()->SetMovementMode(MOVE_Flying);

	Montage_Play(RollMontage);
}

void UGOGCharacterAnimInstance::PlayVaultMontage(const float ObstacleHeight, const float ObstacleDistance, const float Left, const float Right)
{
	GOGCharacter->SetMovementStatus(EMovementStatus::EMS_Parkour);

	GOGCharacter->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GOGCharacter->GetCharacterMovement()->SetMovementMode(MOVE_Flying);

	if(bIsInAir && ObstacleDistance < 100.0f)
	{
		const float InterpHeight = ObstacleHeight - InAirVaultHeight;

		FVector Location = GOGCharacter->GetActorLocation();
		Location.Z += InterpHeight;

		const FVector Forward = GOGCharacter->GetActorForwardVector();
		Location += Forward * (ObstacleDistance * InAirVaultForwardRate);

		GOGCharacter->SetActorLocation(Location);

		FTimerHandle WaitVaultHandle;
		const float WaitTime = Montage_Play(InAirClimbMontage);

		GetWorld()->GetTimerManager().SetTimer(WaitVaultHandle, FTimerDelegate::CreateLambda([&]() {
			if (GOGCharacter)
			{
				Montage_Play(InAirVaultMontage);
			}
		}), WaitTime, false);
	}
	else
	{
		const float InterpHeight = ObstacleHeight - VaultHeight;

		if (InterpHeight < 0.0f)
		{
			Montage_Play(NoHandVaultMontage);
		}
		else
		{
			FVector Location = GOGCharacter->GetActorLocation();
			Location.Z += InterpHeight;
			GOGCharacter->SetActorLocation(Location);

			Left >= Right ? Montage_Play(LeftVaultMontage) : Montage_Play(RightVaultMontage);
		}
	}
}

void UGOGCharacterAnimInstance::PlayClimbMontage(const float ObstacleHeight)
{
	GOGCharacter->SetMovementStatus(EMovementStatus::EMS_Parkour);

	GOGCharacter->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GOGCharacter->GetCharacterMovement()->SetMovementMode(MOVE_Flying);

	FVector Location = GOGCharacter->GetActorLocation();
	Location.Z += ObstacleHeight;
	GOGCharacter->SetActorLocation(Location);

	Montage_Play(ClimbMontage);
}

void UGOGCharacterAnimInstance::PlaySlideMontage(const FVector TargetPosition)
{
	GOGCharacter->SetMovementStatus(EMovementStatus::EMS_Parkour);
	GOGCharacter->SetTargetPosition(TargetPosition);
	GOGCharacter->SetIsSliding(true);

	GOGCharacter->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Montage_Play(SlideMontage);
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

void UGOGCharacterAnimInstance::JumpToAttackMontageSection(const int SectionNum)
{
	const FName SectionName = FName(FString::Printf(TEXT("Attack%d"), SectionNum));

	Montage_JumpToSection(SectionName, AttackMontage);
}

void UGOGCharacterAnimInstance::PlayDeathMontage()
{
	Montage_Play(DeathMontage);
}

void UGOGCharacterAnimInstance::AnimNotify_RollStart() const
{
	GOGCharacter->SetIsRolling(true);
	GOGCharacter->GetCameraBoom()->CameraLagSpeed = 5.0f;
}

void UGOGCharacterAnimInstance::AnimNotify_RollEnd() const
{
	GOGCharacter->SetMovementStatus(EMovementStatus::EMS_Normal);

	GOGCharacter->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GOGCharacter->GetCharacterMovement()->SetMovementMode(MOVE_Walking);

	GOGCharacter->SetIsRolling(false);
}

void UGOGCharacterAnimInstance::AnimNotify_RollHeightInterp() const
{
	FVector Location = GOGCharacter->GetActorLocation();
	Location.Z += 15.0f;

	GOGCharacter->SetActorLocation(Location);
}

void UGOGCharacterAnimInstance::AnimNotify_VaultEnd() const
{
	GOGCharacter->SetMovementStatus(EMovementStatus::EMS_Normal);

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

void UGOGCharacterAnimInstance::AnimNotify_NextAttack()
{
	GOGCharacter->SetCanNextCombo(false);

	if(GOGCharacter->GetIsComboInputOn())
	{
		GOGCharacter->StartComboAttack();
		JumpToAttackMontageSection(GOGCharacter->GetCurrentComboNum());	
	}
}

void UGOGCharacterAnimInstance::AnimNotify_Hit() const
{
	GOGCharacter->GetWeapon()->ActiveCollision();
}

void UGOGCharacterAnimInstance::AnimNotify_HitEnd() const
{
	GOGCharacter->GetWeapon()->DeactiveCollision();
}

void UGOGCharacterAnimInstance::AnimNotify_DeathEnd() const
{
	GOGCharacter->Dead();
}
