// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WarningWidget.generated.h"

/**
 * 
 */
UCLASS()
class GUARDIANSOFGAME_API UWarningWidget final : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta= (BindWidget))
	class UCanvasPanel* CanvasPanel;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* WarningText;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* PopUp;

public:
	FORCEINLINE UWidgetAnimation* GetPopUpAnimaition() const { return PopUp; }

	void SetWarningText(const FString WarningString) const;

	void PlayPopUpAnimation();
};
