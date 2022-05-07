// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GOGMonsterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class GUARDIANSOFGAME_API UGOGMonsterAnimInstance final : public UAnimInstance
{
	GENERATED_BODY()

protected:
	virtual void NativeInitializeAnimation() override;

public:
	UFUNCTION(BlueprintCallable, Category = AnimationProperties)
	void UpdatedAnimationProperties();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	class APawn* Char;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	class AGOGMonster* Monster;
};
