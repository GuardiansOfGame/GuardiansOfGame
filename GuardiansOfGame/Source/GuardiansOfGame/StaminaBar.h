// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StaminaBar.generated.h"

/**
 * 
 */
UCLASS()
class GUARDIANSOFGAME_API UStaminaBar final : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidget))
	class UHorizontalBox* HorizontalBox;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* StaminaBar;
};
