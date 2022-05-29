// Fill out your copyright notice in the Description page of Project Settings.

#include "GOGCharacterWidget.h"

#include "HealthBar.h"
#include "ItemSlot.h"
#include "QuestLogWidget.h"
#include "StaminaBar.h"

void UGOGCharacterWidget::NativeConstruct()
{
	ItemSlotArray = { ItemSlot0, ItemSlot1, ItemSlot2, ItemSlot3, ItemSlot4 };

	for (UItemSlot* ItemSlot : ItemSlotArray)
	{
		ItemSlot->SetVisibility(ESlateVisibility::Hidden);
	}
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

void UGOGCharacterWidget::ViewInventory()
{
	for (UItemSlot* ItemSlot : ItemSlotArray)
	{
		ItemSlot->SetVisibility(ESlateVisibility::Visible);
	}

	PlayAnimation(InventoryPopUp);
}

void UGOGCharacterWidget::HideInventory()
{
	PlayAnimation(InventoryPopUp, 0.0f, 1, EUMGSequencePlayMode::Reverse);

	FTimerHandle UIAnimDelayTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(UIAnimDelayTimerHandle, FTimerDelegate::CreateLambda([&]() {
		for (UItemSlot* ItemSlot : ItemSlotArray)
		{
			ItemSlot->SetVisibility(ESlateVisibility::Hidden);
		}
	}), 0.3f, false);
}
