// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoadingWidget.generated.h"

/**
 * 
 */
UCLASS()
class GUARDIANSOFGAME_API ULoadingWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidget))
	class UImage* Image;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* PopUp;

public:
	void PlayPopUpAnimation(const bool bReversed);
};
