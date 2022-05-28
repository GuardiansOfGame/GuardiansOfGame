// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemSlot.generated.h"

/**
 * 
 */
UCLASS()
class GUARDIANSOFGAME_API UItemSlot final : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* ItemSlotButton;

	UPROPERTY(meta = (BindWidget))
	UTexture2D* ItemImage;

protected:
	UFUNCTION()
	void ItemSlotClicked();
};
