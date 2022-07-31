// Fill out your copyright notice in the Description page of Project Settings.

#include "GameOverWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

#include "GOGCharacterController.h"

void UGameOverWidget::NativeConstruct()
{
	Super::NativeConstruct();

	RetryButton->OnClicked.AddDynamic(this, &UGameOverWidget::RetryButtonClicked);
	TitleButton->OnClicked.AddDynamic(this, &UGameOverWidget::TitleButtonClicked);
	QuitButton->OnClicked.AddDynamic(this, &UGameOverWidget::QuitButtonClicked);
}

void UGameOverWidget::RetryButtonClicked()
{
	AGOGCharacterController* Controller = Cast<AGOGCharacterController>(GetOwningPlayer());

	if(Controller)
	{
		Controller->Respawn();
	}
}

void UGameOverWidget::TitleButtonClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Title"));
}

void UGameOverWidget::QuitButtonClicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}

void UGameOverWidget::PlayPopUpAnimation(const bool bReversed)
{
	if (bReversed)
	{
		PlayAnimation(PopUp, 0.0f, 1, EUMGSequencePlayMode::Reverse);
	}
	else
	{
		PlayAnimation(PopUp);
	}
}
