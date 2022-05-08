// Fill out your copyright notice in the Description page of Project Settings.

#include "StaminaBar.h"

#include "Components/ProgressBar.h"

#include "GOGCharacter.h"

UStaminaBar::UStaminaBar(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	Normal = FLinearColor(0.043763f, 0.104167f, 0.028212f);
	BelowMinimum = FLinearColor(0.90625f, 0.742624f, 0.136882f);
	ExhaustedRecovering = FLinearColor(0.489583f, 0.146341f, 0.043064f);
}

void UStaminaBar::SetStaminaBarPercent(const float CurrentStamina, const float MaxStamina) const
{
	StaminaBar->SetPercent(CurrentStamina / MaxStamina);
}

void UStaminaBar::SetStaminaBarColor(const EStaminaStatus Status) const
{
	FLinearColor StaminaBarColor;

	switch (Status)
	{
	case EStaminaStatus::ESS_Normal:
		StaminaBarColor = Normal;
		break;
	case EStaminaStatus::ESS_BelowMinimum:
		StaminaBarColor = BelowMinimum;
		break;
	case EStaminaStatus::ESS_Exhausted:
		StaminaBarColor = Normal;
		break;
	case EStaminaStatus::ESS_ExhaustedRecovering:
		StaminaBarColor = ExhaustedRecovering;
		break;
	default:
		break;
	}

	StaminaBar->SetFillColorAndOpacity(StaminaBarColor);
}
