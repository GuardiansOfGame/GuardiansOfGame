// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KeyWidget.generated.h"

/**
 * 
 */
UCLASS()
class GUARDIANSOFGAME_API UKeyWidget final : public UUserWidget
{
	GENERATED_BODY()

public:
	explicit UKeyWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* CanvasPanel;

	UPROPERTY(meta = (BindWidget))
	class UImage* Frame;
	UPROPERTY(meta = (BindWidget))
	UImage* Key;

	UPROPERTY(VisibleAnywhere, Category = ImageAsset)
	UTexture2D* FrameImage;
	UPROPERTY(VisibleAnywhere, Category = ImageAsset)
	UTexture2D* KeyImage;
	
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* PopUp;

public:
	FORCEINLINE UWidgetAnimation* GetPopUpAnimaition() const { return PopUp; }
};
