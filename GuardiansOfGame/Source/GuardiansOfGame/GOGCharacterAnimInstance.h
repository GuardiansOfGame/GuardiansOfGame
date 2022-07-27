// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"

#include "GOGCharacter.h"

#include "GOGCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class GUARDIANSOFGAME_API UGOGCharacterAnimInstance final : public UAnimInstance
{
	GENERATED_BODY()

public:
	UGOGCharacterAnimInstance();

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(const float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	AGOGCharacter* GOGCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	bool bIsInAir;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true") )
	EMovementStatus MovementStatus;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = "true"))
	bool bWeaponEquipped;

	float VaultHeight;
	float InAirVaultHeight;
	float InAirVaultForwardRate;

	UPROPERTY(VisibleAnywhere, Category = Parkour)
	UAnimMontage* RollMontage;

	UPROPERTY(VisibleAnywhere, Category = Parkour)
	UAnimMontage* LeftVaultMontage;

	UPROPERTY(VisibleAnywhere, Category = Parkour)
	UAnimMontage* RightVaultMontage;

	UPROPERTY(VisibleAnywhere, Category = Parkour)
	UAnimMontage* NoHandVaultMontage;

	UPROPERTY(VisibleAnywhere, Category = Parkour)
	UAnimMontage* InAirVaultMontage;

	UPROPERTY(VisibleAnywhere, Category = Parkour)
	UAnimMontage* ClimbMontage;

	UPROPERTY(VisibleAnywhere, Category = Parkour)
	UAnimMontage* InAirClimbMontage;

	UPROPERTY(VisibleAnywhere, Category = Parkour)
	UAnimMontage* SlideMontage;

	UPROPERTY(VisibleAnywhere, Category = Combat)
	UAnimMontage* EquipMontage;

	UPROPERTY(VisibleAnywhere, Category = Combat)
	UAnimMontage* UnequipMontage;

	UPROPERTY(VisibleAnywhere, Category = Combat)
	UAnimMontage* AttackMontage;

	UPROPERTY(VisibleAnywhere, Category = Combat)
	UAnimMontage* DeathMontage;

public:
	FORCEINLINE UAnimMontage* GetClimbMontage() const { return ClimbMontage; }
	FORCEINLINE UAnimMontage* GetSlideMontage() const { return SlideMontage; }
	FORCEINLINE UAnimMontage* GetAttackMontage() const { return AttackMontage; }

	void PlayRollMontage();
	void PlayVaultMontage(const float ObstacleHeight, const float ObstacleDistance, const float Left, const float Right);
	void PlayClimbMontage(const float ObstacleHeight);
	void PlaySlideMontage(const FVector TargetPosition);

	void PlayEquipMontage();
	void PlayUnEquipMontage();

	void PlayAttackMontage();
	void JumpToAttackMontageSection(const int SectionNum);

	void PlayDeathMontage();

	UFUNCTION()
	void AnimNotify_RollStart() const;
	UFUNCTION()
	void AnimNotify_RollEnd() const;
	UFUNCTION()
	void AnimNotify_RollHeightInterp() const;

	UFUNCTION()
	void AnimNotify_VaultEnd() const;

	UFUNCTION()
	void AnimNotify_Equip();
	UFUNCTION()
	void AnimNotify_Unequip();

	UFUNCTION()
	void AnimNotify_NextAttack();

	UFUNCTION()
	void AnimNotify_Hit() const;
	UFUNCTION()
	void AnimNotify_HitEnd() const;

	UFUNCTION()
	void AnimNotify_DeathEnd() const;
};
