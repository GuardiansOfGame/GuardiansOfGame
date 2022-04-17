// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainController.generated.h"

/**
 * 
 */
UCLASS()
class GUARDIANSOFGAME_API AMainController final : public APlayerController
{
	GENERATED_BODY()

public:
	AMainController();

protected:
	virtual void OnPossess(APawn* InPawn) override;

private:
	UPROPERTY(VisibleAnywhere, Category = Player)
	class AMain* Main;

public:
	
};
