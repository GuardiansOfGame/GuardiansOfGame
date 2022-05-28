// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemSlot.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDele_Dynamic_OneParam, int, SlotNumber);

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
	class UImage* ItemImage;

	UPROPERTY(VisibleAnywhere, Category = SlotInfo)
	UTexture2D* ItemTexture;

	UPROPERTY(VisibleAnywhere, Category = SlotInfo)
	FSlateBrush ItemImageBrush;

	UPROPERTY(EditAnywhere, Category = SlotInfo)
	int SlotNumber;

protected:
	UFUNCTION()
	void ItemSlotClicked();

public:
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = Event)
	FDele_Dynamic_OneParam ItemSlotClicked_Dynamic;
};
