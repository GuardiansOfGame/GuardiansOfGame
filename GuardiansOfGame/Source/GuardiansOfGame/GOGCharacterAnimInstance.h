// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	class AGOGCharacter* GOGCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	bool bIsInAir;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = "true"))
	bool bWeaponEquipped;

	float VaultHeight;

	UPROPERTY(VisibleAnywhere, Category = Parkour)
	UAnimMontage* RollMontage;

	UPROPERTY(VisibleAnywhere, Category = Parkour)
	UAnimMontage* LeftVaultMontage;

	UPROPERTY(VisibleAnywhere, Category = Parkour)
	UAnimMontage* RightVaultMontage;

	UPROPERTY(VisibleAnywhere, Category = Parkour)
	UAnimMontage* NoHandVaultMontage;

	UPROPERTY(VisibleAnywhere, Category = Parkour)
	UAnimMontage* ClimbMontage;

	UPROPERTY(VisibleAnywhere, Category = Parkour)
	UAnimMontage* SlideMontage;

	UPROPERTY(VisibleAnywhere, Category = Combat)
	UAnimMontage* EquipMontage;

	UPROPERTY(VisibleAnywhere, Category = Combat)
	UAnimMontage* UnequipMontage;

	UPROPERTY(VisibleAnywhere, Category = Combat)
	UAnimMontage* AttackMontage;

public:
	void PlayRollMontage();
	void PlayVaultMontage(const float ObstacleHeight, const float Left, const float Right);
	void PlayClimbMontage(const float ObstacleHeight);
	void PlaySlideMontage(const FVector TargetPosition);

	void PlayEquipMontage();
	void PlayUnEquipMontage();

	void PlayAttackMontage();

	UFUNCTION()
	void AnimNotify_RollStart() const;
	UFUNCTION()
	void AnimNotify_RollEnd() const;

	UFUNCTION()
	void AnimNotify_VaultEnd() const;

	UFUNCTION()
	void AnimNotify_Equip();
	UFUNCTION()
	void AnimNotify_Unequip();
};
