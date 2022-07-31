// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "CustomStruct.h"
#include "GOGCharacterWidget.h"

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
	UGOGCharacterWidget* GOGCharacterWidget;

	TSubclassOf<class ULoadingWidget> LoadingWidgetClass;
	UPROPERTY(VisibleAnywhere, Category = Widget)
	ULoadingWidget* LoadingWidget;

	TSubclassOf<class UPauseWidget> PauseWidgetClass;
	UPROPERTY(VisibleAnywhere, Category = Widget)
	UPauseWidget* PauseWidget;

	TSubclassOf<class UGameOverWidget> GameOverWidgetClass;
	UPROPERTY(VisibleAnywhere, Category = Widget)
	UGameOverWidget* GameOverWidget;

	TSubclassOf<class UDialogueWidget> DialogueWidgetClass;
	UPROPERTY(VisibleAnywhere, Category = Widget)
	class UDialogueWidget* DialogueWidget;

	TSubclassOf<class UHealthBar> MonsterHealthWidgetClass;
	UPROPERTY(VisibleAnywhere, Category = Widget)
	class UHealthBar* MonsterHealthWidget;

public:
	FORCEINLINE TArray<FCustomItemInfo> GetInventory() const { return GOGCharacterWidget->GetInventory(); }
	FORCEINLINE void SetInventory(const TArray<FCustomItemInfo> CurrentInventory) const { GOGCharacterWidget->SetInventory(CurrentInventory); }

	void Loading(const bool bReversed, const bool bUIRemoved) const;

	void BeginChat(const TArray<FString> Strings, const FString Name);
	void EndChat();

	void TogglePause(const bool bPause);

	void GameOver();
	void Respawn();

	void SetHealthBarPercent(const float CurrentHealth, const float MaxHealth) const;
	void SetStaminaBarPercent(const float CurrentStamina, const float MaxStamina) const;

	void SetStaminaBarColor(const EStaminaStatus Status) const;

	void InitQuestLog(const class UGOGCharacterStatComponent* StatComponent, const int CurQuestNum) const;
	void UpdateQuestLog(UGOGCharacterStatComponent* StatComponent, const int TaskNum) const;

	void SetQuestLogVisibillity(const UGOGCharacterStatComponent* StatComponent, const bool bForceHidden = false) const;

	void ToggleInventory(const bool bVisible);

	void PickUpItem(const FCustomItemInfo ItemInfo) const;
};