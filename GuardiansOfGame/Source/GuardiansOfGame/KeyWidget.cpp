// Fill out your copyright notice in the Description page of Project Settings.

#include "KeyWidget.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Image.h"

void UKeyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	FrameImage = LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/CustomContent/Image/UI/KeyFrameImage.KeyFrameImage'"));
	KeyImage = LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/CustomContent/Image/UI/FKeyInsideImage.FKeyInsideImage'"));

	Frame->SetBrushFromTexture(FrameImage);
	Key->SetBrushFromTexture(KeyImage);
}