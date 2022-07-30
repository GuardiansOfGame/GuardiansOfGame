// Fill out your copyright notice in the Description page of Project Settings.

#include "GameOverWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UGameOverWidget::NativeConstruct()
{
	Super::NativeConstruct();

	RetryButton->OnClicked.AddDynamic(this, &UGameOverWidget::RetryButtonClicked);
	TitleButton->OnClicked.AddDynamic(this, &UGameOverWidget::TitleButtonClicked);
	QuitButton->OnClicked.AddDynamic(this, &UGameOverWidget::QuitButtonClicked);
}

void UGameOverWidget::RetryButtonClicked()
{
}

void UGameOverWidget::TitleButtonClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Title"));
}

void UGameOverWidget::QuitButtonClicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}

void UGameOverWidget::PlayPopUpAnimation()
{
	PlayAnimation(PopUp);
}
