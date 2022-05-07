// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GOGCharacterWidget.generated.h"

/**
 * 
 */
UCLASS()
class GUARDIANSOFGAME_API UGOGCharacterWidget final : public UUserWidget
{
	GENERATED_BODY()

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
};
