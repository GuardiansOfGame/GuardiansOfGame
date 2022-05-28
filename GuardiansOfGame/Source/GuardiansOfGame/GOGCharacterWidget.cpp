// Fill out your copyright notice in the Description page of Project Settings.

#include "GOGCharacterWidget.h"

#include "HealthBar.h"
#include "QuestLogWidget.h"
#include "StaminaBar.h"

void UGOGCharacterWidget::NativeConstruct()
{
	ItemSlotArray = { ItemSlot0, ItemSlot1, ItemSlot2, ItemSlot3, ItemSlot4 };
}

void UGOGCharacterWidget::InitQuestLog(const FQuest InputQuest) const
{
	QuestLog->Init(InputQuest);
}

void UGOGCharacterWidget::SetHealthBarPercent(const float CurrentHealth, const float MaxHealth) const
{
	HealthBar->SetHealthBarPercent(CurrentHealth, MaxHealth);
}

void UGOGCharacterWidget::SetStaminaBarPercent(const float CurrentStamina, const float MaxStamina) const
{
	StaminaBar->SetStaminaBarPercent(CurrentStamina, MaxStamina);
}

void UGOGCharacterWidget::SetStaminaBarColor(const EStaminaStatus Status) const
{
	StaminaBar->SetStaminaBarColor(Status);
}
