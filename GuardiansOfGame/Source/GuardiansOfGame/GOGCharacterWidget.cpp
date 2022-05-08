// Fill out your copyright notice in the Description page of Project Settings.

#include "GOGCharacterWidget.h"

#include "HealthBar.h"
#include "StaminaBar.h"

void UGOGCharacterWidget::SetHealthBarPercent(const float CurrentHealth, const float MaxHealth) const
{
	HealthBar->SetHealthBarPercent(CurrentHealth, MaxHealth);
}

void UGOGCharacterWidget::SetStaminaBarPercent(const float CurrentStamina, const float MaxStamina) const
{
	StaminaBar->SetStaminaBarPercent(CurrentStamina, MaxStamina);
}
