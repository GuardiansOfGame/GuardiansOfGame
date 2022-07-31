// Fill out your copyright notice in the Description page of Project Settings.

#include "LoadingWidget.h"

void ULoadingWidget::PlayPopUpAnimation(const bool bReversed)
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
