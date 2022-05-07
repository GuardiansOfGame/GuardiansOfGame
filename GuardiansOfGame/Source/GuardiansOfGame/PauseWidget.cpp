// Fill out your copyright notice in the Description page of Project Settings.

#include "PauseWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

#include "GOGCharacterController.h"

UPauseWidget::UPauseWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bIsFocusable = true;
}

void UPauseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetKeyboardFocus();

	ResumeButton->OnClicked.AddDynamic(this, &UPauseWidget::ResumeButtonClicked);
	TitleButton->OnClicked.AddDynamic(this, &UPauseWidget::TitleButtonClicked);
	QuitButton->OnClicked.AddDynamic(this, &UPauseWidget::QuitButtonClicked);
}

FReply UPauseWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	Super::NativeOnKeyDown(InGeometry, InKeyEvent);

	if(InKeyEvent.GetKey() == EKeys::P || InKeyEvent.GetKey() == EKeys::Escape)
	{
		AGOGCharacterController* Controller = Cast<AGOGCharacterController>(GetOwningPlayer());
		if (Controller)
		{
			if(Controller->IsPaused())
			{
				Controller->TogglePause(false);
				return FReply::Handled();
			}
		}
	}

	return FReply::Unhandled();
}

void UPauseWidget::ResumeButtonClicked()
{
	AGOGCharacterController* Controller = Cast<AGOGCharacterController>(GetOwningPlayer());
	if(Controller)
	{
		if (Controller->IsPaused())
		{
			Controller->TogglePause(false);
		}
	}
}

void UPauseWidget::TitleButtonClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Title"));
}

void UPauseWidget::QuitButtonClicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}

void UPauseWidget::PlayPopUpAnimation(const bool bReversed)
{
	if(bReversed)
	{
		PlayAnimation(PopUp, 0.0f, 1, EUMGSequencePlayMode::Reverse);
	}
	else
	{
		PlayAnimation(PopUp);
	}
}
