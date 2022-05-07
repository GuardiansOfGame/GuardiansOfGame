// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TitlePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GUARDIANSOFGAME_API ATitlePlayerController final : public APlayerController
{
	GENERATED_BODY()

public:
	ATitlePlayerController();

protected:
	virtual void BeginPlay() override;

private:
	TSubclassOf<class UTitleWidget> TitleWidgetClass;
	UPROPERTY(VisibleAnywhere, Category = Widget)
	class UTitleWidget* TitleWidget;
};
