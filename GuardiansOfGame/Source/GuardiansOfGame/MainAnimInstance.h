// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MainAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class GUARDIANSOFGAME_API UMainAnimInstance final : public UAnimInstance
{
	GENERATED_BODY()

public:
	UMainAnimInstance();

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(const float DeltaSeconds) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	class AMain* Main;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	bool bIsInAir;

	UPROPERTY(VisibleAnywhere, Category = Montage)
	UAnimMontage* RollMontage;

	UPROPERTY(VisibleAnywhere, Category = Montage)
	UAnimMontage* VaultMontage;

	UPROPERTY(VisibleAnywhere, Category = Montage)
	UAnimMontage* SlideMontage;

public:
	void PlayRollMontage();
	void PlayVaultMontage(const float ObstacleHeight, const float Left, const float Right);
	void PlaySlideMontage(const FVector TargetPosition);

	UFUNCTION()
	void AnimNotify_RollStart() const;
	UFUNCTION()
	void AnimNotify_RollEnd() const;

	UFUNCTION()
	void AnimNotify_VaultEnd() const;
};
