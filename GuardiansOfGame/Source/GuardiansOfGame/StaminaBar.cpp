// Fill out your copyright notice in the Description page of Project Settings.

#include "StaminaBar.h"

#include "Components/ProgressBar.h"

void UStaminaBar::SetStaminaBarPercent(const float CurrentStamina, const float MaxStamina) const
{
	StaminaBar->SetPercent(CurrentStamina / MaxStamina);
}
