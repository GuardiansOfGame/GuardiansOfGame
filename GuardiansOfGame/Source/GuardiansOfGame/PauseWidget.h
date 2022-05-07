// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseWidget.generated.h"

/**
 * 
 */
UCLASS()
class GUARDIANSOFGAME_API UPauseWidget final : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UBackgroundBlur* Blur;

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* ButtonBox;

	UPROPERTY(meta = (BindWidget))
	class UButton* ResumeButton;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ResumeText;

	UPROPERTY(meta = (BindWidget))
	UButton* TitleButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TitleText;

	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* QuitText;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* PopUp;

protected:
	UFUNCTION()
	void ResumeButtonClicked();

	UFUNCTION()
	void TitleButtonClicked();

	UFUNCTION()
	void QuitButtonClicked();

public:
	void PlayPopUpAnimation(const bool bReversed);
};
