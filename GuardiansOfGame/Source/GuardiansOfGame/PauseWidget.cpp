// Fill out your copyright notice in the Description page of Project Settings.

#include "PauseWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

#include "GOGCharacterController.h"

void UPauseWidget::NativeConstruct()
{
	ResumeButton->OnClicked.AddDynamic(this, &UPauseWidget::ResumeButtonClicked);
	TitleButton->OnClicked.AddDynamic(this, &UPauseWidget::TitleButtonClicked);
	QuitButton->OnClicked.AddDynamic(this, &UPauseWidget::QuitButtonClicked);
}

void UPauseWidget::ResumeButtonClicked()
{
	AGOGCharacterController* Controller = Cast<AGOGCharacterController>(GetOwningPlayer());
	if(Controller)
	{
		Controller->TogglePause(false);
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
