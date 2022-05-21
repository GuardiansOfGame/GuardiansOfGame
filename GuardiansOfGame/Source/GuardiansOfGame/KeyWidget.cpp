// Fill out your copyright notice in the Description page of Project Settings.

#include "KeyWidget.h"

#include "Components/Image.h"

UKeyWidget::UKeyWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	FrameImage = LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/CustomContent/Image/KeyFrameImage.KeyFrameImage'"));
	KeyImage = LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/CustomContent/Image/FKeyInsideImage.FKeyInsideImage'"));
}

void UKeyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Frame->SetBrushFromTexture(FrameImage);
	Key->SetBrushFromTexture(KeyImage);
}