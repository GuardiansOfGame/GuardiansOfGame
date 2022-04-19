// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "CustomStruct.h"

#include "MainStatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GUARDIANSOFGAME_API UMainStatComponent final : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMainStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;

private:
	UPROPERTY(VisibleAnywhere, Category = GameInstance)
	class UGOGGameInstance* GameInstance;

	UPROPERTY(VisibleAnywhere, Category = Quest)
	FQuestBooleans QuestProgress;

	UPROPERTY(VisibleAnywhere, Category = Quest)
	int CurQuestNum;

public:
	FORCEINLINE FQuestBooleans GetQuestProgress() const { return QuestProgress; }

	FORCEINLINE int GetCurQuestNum() const { return CurQuestNum; }
	FORCEINLINE void SetCurQuestNum(const int Num) { CurQuestNum = Num; }

	FORCEINLINE void SetCurQuestAccept(const bool bValue) { QuestProgress.CurQuestAccept = bValue; }
	FORCEINLINE void SetCurQuestSuccess(const bool bValue) { QuestProgress.CurQuestSuccess = bValue; }

	FORCEINLINE void SetQuestAcceptArr(const int QuestNum, const bool bValue) { QuestProgress.QuestAcceptArr[QuestNum] = bValue; }
	FORCEINLINE void SetQuestSuccessArr(const int QuestNum, const bool bValue) { QuestProgress.QuestSuccessArr[QuestNum] = bValue; }

	void Init();
	void Save() const;
};
