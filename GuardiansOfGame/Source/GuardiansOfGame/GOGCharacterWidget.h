// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "CustomStruct.h"

#include "GOGCharacterWidget.generated.h"

enum class EStaminaStatus : uint8;
/**
 * 
 */
UCLASS()
class GUARDIANSOFGAME_API UGOGCharacterWidget final : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* CanvasPanel;

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* LeftBox;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* LeftTopBox;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* HealthBarBox;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* StaminaBarBox;

	UPROPERTY(meta = (BindWidget))
	class UHealthBar* HealthBar;

	UPROPERTY(meta = (BindWidget))
	class UStaminaBar* StaminaBar;

	UPROPERTY(meta = (BindWidget))
	class UQuestLogWidget* QuestLog;

	UPROPERTY(meta = (BindWidget))
	class UItemSlot* ItemSlot0;

	UPROPERTY(meta = (BindWidget))
	UItemSlot* ItemSlot1;

	UPROPERTY(meta = (BindWidget))
	UItemSlot* ItemSlot2;

	UPROPERTY(meta = (BindWidget))
	UItemSlot* ItemSlot3;

	UPROPERTY(meta = (BindWidget))
	UItemSlot* ItemSlot4;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* ItemActionMenuBox;

	UPROPERTY(meta = (BindWidget))
	class UButton* UseItemButton;

	UPROPERTY(meta = (BindWidget))
	UButton* DropItemButton;

	UPROPERTY(meta = (BindWidget))
	UButton* ItemActionCancelButton;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* UseText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* DropText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CancelText;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* InventoryPopUp;

	UPROPERTY()
	TArray<UItemSlot*> ItemSlotArray;

	UPROPERTY()
	TArray<FCustomItemInfo> Inventory;

	int ClickedSlotNumber;

protected:
	UFUNCTION()
	void UseItemButtonClicked();

	UFUNCTION()
	void DropItemButtonClicked();

	UFUNCTION()
	void ItemActionCancelButtonClicked();

public:
	FORCEINLINE UQuestLogWidget* GetQuestLogWidget() const { return QuestLog; }

	FORCEINLINE TArray<FCustomItemInfo> GetInventory() const { return Inventory; }
	FORCEINLINE void SetInventory(const TArray<FCustomItemInfo> CurrentInventory) { Inventory = CurrentInventory; }

	void InitQuestLog(const FQuest InputQuest) const;

	void SetHealthBarPercent(const float CurrentHealth, const float MaxHealth) const;
	void SetStaminaBarPercent(const float CurrentStamina, const float MaxStamina) const;

	void SetStaminaBarColor(const EStaminaStatus Status) const;

	void ViewInventory();
	void HideInventory();

	void AddItem(const FCustomItemInfo ItemInfo);

	void RefreshInventory();

	UFUNCTION()
	void ViewItemActionMenuBox(const int SlotNumber);
};
