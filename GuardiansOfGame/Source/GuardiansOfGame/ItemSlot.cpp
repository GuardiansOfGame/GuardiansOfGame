// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemSlot.h"

#include "Components/Button.h"

void UItemSlot::NativeConstruct()
{
	Super::NativeConstruct();

	ItemSlotButton->OnClicked.AddDynamic(this, &UItemSlot::ItemSlotClicked);
}

void UItemSlot::NativeDestruct()
{
}

void UItemSlot::ItemSlotClicked()
{
}
