// Fill out your copyright notice in the Description page of Project Settings.

#include "TitleWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UTitleWidget::NativeConstruct()
{
	Super::NativeConstruct();

	StartButton->OnClicked.AddDynamic(this, &UTitleWidget::StartButtonClicked);
	QuitButton->OnClicked.AddDynamic(this, &UTitleWidget::QuitButtonClicked);
}

void UTitleWidget::StartButtonClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("TestMap1")));
}

void UTitleWidget::QuitButtonClicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}
