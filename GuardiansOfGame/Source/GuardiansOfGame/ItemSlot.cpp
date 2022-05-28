// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemSlot.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Button.h"
#include "Components/Image.h"

void UItemSlot::NativeConstruct()
{
	Super::NativeConstruct();

	SlotNumber = 0;
	ItemSlotButton->OnClicked.AddDynamic(this, &UItemSlot::ItemSlotClicked);

	ItemImageBrush = UWidgetBlueprintLibrary::MakeBrushFromTexture(ItemTexture);
	ItemImage->SetBrush(ItemImageBrush);
}

void UItemSlot::NativeDestruct()
{
	ItemSlotClicked_Dynamic.Clear();
}

void UItemSlot::ItemSlotClicked()
{
	if(ItemSlotClicked_Dynamic.IsBound())
	{
		ItemSlotClicked_Dynamic.Broadcast(SlotNumber);
	}
}
