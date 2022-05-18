// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "CustomStruct.h"

#include "GOGGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class GUARDIANSOFGAME_API UGOGGameInstance final : public UGameInstance
{
	GENERATED_BODY()

public:
	UGOGGameInstance();

protected:
	virtual void Init() override;
	virtual void Shutdown() override;
	virtual void StartGameInstance() override;

private:
	UPROPERTY(VisibleAnywhere, Category = Quest)
	FQuestBooleans QuestProgress;

	int MaxQuestNum;
	int CurQuestNum;

	UPROPERTY(VisibleAnywhere, Category = Quest)
	class UDataTable* QuestDataTable;

	UPROPERTY(VisibleAnywhere, Category = Quest)
	TArray<FQuest> Quests;

public:
	FORCEINLINE FQuestBooleans GetQuestProgress() const { return QuestProgress; }
	FORCEINLINE void SetQuestProgress(const FQuestBooleans Quest) { QuestProgress = Quest; }

	FORCEINLINE TArray<FQuest> GetQuests() const { return Quests; }
	FORCEINLINE void SetQuests(const TArray<FQuest> CurrentQuests) { Quests = CurrentQuests; }

	FORCEINLINE int GetCurQuestNum() const { return CurQuestNum; }
	FORCEINLINE void SetCurQuestNum(const int Num) { CurQuestNum = Num; }
};
