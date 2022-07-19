// Fill out your copyright notice in the Description page of Project Settings.

#include "GOGCharacterWidget.h"

#include "Components/Button.h"
#include "Components/VerticalBox.h"

#include "HealthBar.h"
#include "ItemInterface.h"
#include "ItemSlot.h"
#include "QuestLogWidget.h"
#include "StaminaBar.h"
#include "WarningWidget.h"

void UGOGCharacterWidget::NativeConstruct()
{
	ItemSlotArray = { ItemSlot0, ItemSlot1, ItemSlot2, ItemSlot3, ItemSlot4 };

	for(int i = 0; i < ItemSlotArray.Num(); ++i)
	{
		ItemSlotArray[i]->SetVisibility(ESlateVisibility::Hidden);

		ItemSlotArray[i]->SetSlotNumber(i);
		ItemSlotArray[i]->ItemSlotClicked_Dynamic.AddDynamic(this, &UGOGCharacterWidget::ViewItemActionMenuBox);
	}

	Inventory = {};

	ItemActionMenuBox->SetVisibility(ESlateVisibility::Hidden);

	UseItemButton->OnClicked.AddDynamic(this, &UGOGCharacterWidget::UseItemButtonClicked);
	DropItemButton->OnClicked.AddDynamic(this, &UGOGCharacterWidget::DropItemButtonClicked);
	ItemActionCancelButton->OnClicked.AddDynamic(this, &UGOGCharacterWidget::ItemActionCancelButtonClicked);

	ClickedSlotNumber = 0;

	WarningWidget->SetVisibility(ESlateVisibility::Hidden);
	WarningWidget->SetWarningText(TEXT("해당 아이템을 사용할 수 있는 위치가 아닙니다."));
}

void UGOGCharacterWidget::UseItemButtonClicked()
{
	if(Inventory.IsValidIndex(ClickedSlotNumber))
	{
		bool bItemUsed{};

		AActor* Item = Inventory[ClickedSlotNumber].Item;
		IItemInterface* ItemInterface = Cast<IItemInterface>(Item);
		if(ItemInterface)
		{
			bItemUsed = ItemInterface->UseItem();
		}

		if(bItemUsed)
		{
			Inventory.RemoveAtSwap(ClickedSlotNumber);
			RefreshInventory();
		}
		else
		{
			WarningWidget->SetWarningText(TEXT("해당 아이템을 사용할 수 있는 위치가 아닙니다."));
			WarningWidget->SetVisibility(ESlateVisibility::Visible);

			WarningWidget->PlayPopUpAnimation();

			FTimerHandle UIAnimDelayTimerHandle;
			GetWorld()->GetTimerManager().SetTimer(UIAnimDelayTimerHandle, FTimerDelegate::CreateLambda([&]() {
				WarningWidget->SetVisibility(ESlateVisibility::Hidden);
			}), 0.6f, false);
		}

		ItemActionMenuBox->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UGOGCharacterWidget::DropItemButtonClicked()
{
	if(Inventory.IsValidIndex(ClickedSlotNumber))
	{
		Inventory.RemoveAtSwap(ClickedSlotNumber);
		RefreshInventory();

		ItemActionMenuBox->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UGOGCharacterWidget::ItemActionCancelButtonClicked()
{
	ItemActionMenuBox->SetVisibility(ESlateVisibility::Hidden);
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
	ItemActionMenuBox->SetVisibility(ESlateVisibility::Hidden);

	PlayAnimation(InventoryPopUp, 0.0f, 1, EUMGSequencePlayMode::Reverse);

	FTimerHandle UIAnimDelayTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(UIAnimDelayTimerHandle, FTimerDelegate::CreateLambda([&]() {
		for (UItemSlot* ItemSlot : ItemSlotArray)
		{
			ItemSlot->SetVisibility(ESlateVisibility::Hidden);
		}
	}), 0.3f, false);
}

void UGOGCharacterWidget::AddItem(const FCustomItemInfo ItemInfo)
{
	if(Inventory.Num() < MAX_ITEM_NUM)
	{
		Inventory.Add(ItemInfo);
	}
}

void UGOGCharacterWidget::RefreshInventory()
{
	for(int i = 0; i < MAX_ITEM_NUM; ++i)
	{
		if(i < Inventory.Num())
		{
			ItemSlotArray[i]->SetItemImage(Inventory[i].Image);
		}
		else
		{
			ItemSlotArray[i]->SetItemImage(nullptr);
		}
	}
}

void UGOGCharacterWidget::ViewItemActionMenuBox(const int SlotNumber)
{
	if(SlotNumber < Inventory.Num())
	{
		ClickedSlotNumber = SlotNumber;
		const FVector2D RenderTranslation = ItemSlotArray[ClickedSlotNumber]->RenderTransform.Translation;

		ItemActionMenuBox->SetRenderTranslation(RenderTranslation);
		ItemActionMenuBox->SetVisibility(ESlateVisibility::Visible);
	}
}
