// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GOGCharacterController.generated.h"

/**
 *
 */
UCLASS()
class GUARDIANSOFGAME_API AGOGCharacterController final : public APlayerController
{
	GENERATED_BODY()

public:
	AGOGCharacterController();

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = Player)
	class AGOGCharacter* GOGCharacter;

	TSubclassOf<class UGOGCharacterWidget> GOGCharacterWidgetClass;
	UPROPERTY(VisibleAnywhere, Category = Widget)
	class UGOGCharacterWidget* GOGCharacterWidget;

	TSubclassOf<class UPauseWidget> PauseWidgetClass;
	UPROPERTY(VisibleAnywhere, Category = Widget)
	class UPauseWidget* PauseWidget;

	TSubclassOf<class UDialogueWidget> DialogueWidgetClass;
	UPROPERTY(VisibleAnywhere, Category = Widget)
	class UDialogueWidget* DialogueWidget;

public:
	void BeginChat(const TArray<FString> Strings, const FString Name);
	void EndChat();

	void TogglePause(const bool bPause);

	void SetHealthBarPercent(const float CurrentHealth, const float MaxHealth) const;
	void SetStaminaBarPercent(const float CurrentStamina, const float MaxStamina) const;
};