// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StaminaBar.generated.h"

enum class EStaminaStatus : uint8;

/**
 * 
 */
UCLASS()
class GUARDIANSOFGAME_API UStaminaBar final : public UUserWidget
{
	GENERATED_BODY()

public:
	explicit UStaminaBar(const FObjectInitializer& ObjectInitializer);

private:
	UPROPERTY(meta = (BindWidget))
	class UHorizontalBox* HorizontalBox;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* StaminaBar;

	FLinearColor Normal;
	FLinearColor BelowMinimum;
	FLinearColor ExhaustedRecovering;

public:
	void SetStaminaBarPercent(const float CurrentStamina, const float MaxStamina) const;
	void SetStaminaBarColor(const EStaminaStatus Status) const;
};
