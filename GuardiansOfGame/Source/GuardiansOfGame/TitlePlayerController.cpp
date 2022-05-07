// Fill out your copyright notice in the Description page of Project Settings.

#include "TitlePlayerController.h"

#include "TitleWidget.h"

ATitlePlayerController::ATitlePlayerController()
{
	static ConstructorHelpers::FClassFinder<UTitleWidget> TitleWidgetClassAsset(TEXT("WidgetBlueprint'/Game/Widgets/TitleWidget_BP.TitleWidget_BP_C'"));
	if (TitleWidgetClassAsset.Succeeded())
	{
		TitleWidgetClass = TitleWidgetClassAsset.Class;
	}
}

void ATitlePlayerController::BeginPlay()
{
	if (TitleWidgetClass)
	{
		TitleWidget = CreateWidget<UTitleWidget>(this, TitleWidgetClass);
		TitleWidget->AddToViewport();
	}
}
