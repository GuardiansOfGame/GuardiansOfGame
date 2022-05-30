// Fill out your copyright notice in the Description page of Project Settings.

#include "WarningWidget.h"

#include "Components/TextBlock.h"

void UWarningWidget::SetWarningText(const FString WarningString) const
{
	const FText Text = FText::FromString(WarningString);
	WarningText->SetText(Text);
}

void UWarningWidget::PlayPopUpAnimation()
{
	PlayAnimation(PopUp);
	SetVisibility(ESlateVisibility::Hidden);
}
