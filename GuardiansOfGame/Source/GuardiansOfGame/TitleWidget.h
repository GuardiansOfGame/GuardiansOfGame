// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TitleWidget.generated.h"

/**
 * 
 */
UCLASS()
class GUARDIANSOFGAME_API UTitleWidget final : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* CanvasPanel;

	UPROPERTY(meta = (BindWidget))
	class UImage* Background;

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* NameBox;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* ButtonBox;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* GameName;

	UPROPERTY(meta = (BindWidget))
	class UButton* StartButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* StartText;

	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* QuitText;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* PopUp;

protected:
	UFUNCTION()
	void StartButtonClicked();

	UFUNCTION()
	void QuitButtonClicked();

public:
	FORCEINLINE UWidgetAnimation* GetPopUpAnimaition() const { return PopUp; }
};
