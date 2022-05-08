// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthBar.h"

#include "Components/ProgressBar.h"

void UHealthBar::SetHealthBarPercent(const float CurrentHealth, const float MaxHealth) const
{
	HealthBar->SetPercent(CurrentHealth / MaxHealth);
}
