// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "NPCAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class GUARDIANSOFGAME_API UNPCAnimInstance final : public UAnimInstance
{
	GENERATED_BODY()

public:
	UNPCAnimInstance();

protected:
	virtual void NativeInitializeAnimation() override;

private:
	UPROPERTY(VisibleAnywhere, Category = Character)
	class ANPC* NPC;
};
