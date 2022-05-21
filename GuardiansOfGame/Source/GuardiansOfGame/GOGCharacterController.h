// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GOGCharacterController.generated.h"

enum class EStaminaStatus : uint8;
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

	UPROPERTY(VisibleAnywhere, Category = GameInstance)
	class UGOGGameInstance* GameInstance;

	TSubclassOf<class UGOGCharacterWidget> GOGCharacterWidgetClass;
	UPROPERTY(VisibleAnywhere, Category = Widget)
	class UGOGCharacterWidget* GOGCharacterWidget;

	TSubclassOf<class UPauseWidget> PauseWidgetClass;
	UPROPERTY(VisibleAnywhere, Category = Widget)
	class UPauseWidget* PauseWidget;

	TSubclassOf<class UDialogueWidget> DialogueWidgetClass;
	UPROPERTY(VisibleAnywhere, Category = Widget)
	class UDialogueWidget* DialogueWidget;

	TSubclassOf<class UHealthBar> MonsterHealthWidgetClass;
	UPROPERTY(VisibleAnywhere, Category = Widget)
	class UHealthBar* MonsterHealthWidget;

public:
	void BeginChat(const TArray<FString> Strings, const FString Name);
	void EndChat();

	void TogglePause(const bool bPause);

	void SetHealthBarPercent(const float CurrentHealth, const float MaxHealth) const;
	void SetStaminaBarPercent(const float CurrentStamina, const float MaxStamina) const;

	void SetStaminaBarColor(const EStaminaStatus Status) const;

	void InitQuestLog(const class UGOGCharacterStatComponent* StatComponent, const int CurQuestNum) const;

	void SetQuestLogVisibillity(const UGOGCharacterStatComponent* StatComponent, const bool bForceHidden = false) const;
};