// Fill out your copyright notice in the Description page of Project Settings.

#include "GOGCharacterStatComponent.h"

#include "GOGCharacterController.h"
#include "GOGGameInstance.h"

// Sets default values for this component's properties
UGOGCharacterStatComponent::UGOGCharacterStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}


// Called when the game starts
void UGOGCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UGOGCharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();

	Init();
}

void UGOGCharacterStatComponent::SetTaskCompleted(const int TaskNum)
{
	Quests[CurQuestNum].Tasks[TaskNum].bIsCompleted = true;

	if(Quests[CurQuestNum].Tasks[TaskNum].Type.bIsBattleQuest)
	{
		const int Goal = Quests[CurQuestNum].Tasks[TaskNum].Type.Goal;
		Quests[CurQuestNum].Tasks[TaskNum].Type.Current = Goal;
	}
}

void UGOGCharacterStatComponent::SetBattleTaskProgress(const int TaskNum)
{
	++Quests[CurQuestNum].Tasks[TaskNum].Type.Current;
	const int Goal = Quests[CurQuestNum].Tasks[TaskNum].Type.Goal;

	if(Quests[CurQuestNum].Tasks[TaskNum].Type.Current == Goal)
	{
		SetTaskCompleted(TaskNum);
	}
}

void UGOGCharacterStatComponent::Init()
{
	GameInstance = Cast<UGOGGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		QuestProgress = GameInstance->GetQuestProgress();
		CurQuestNum = GameInstance->GetCurQuestNum();

		Quests = GameInstance->GetQuests();
	}
}

void UGOGCharacterStatComponent::Save(const AGOGCharacterController* Controller) const
{
	if (GameInstance)
	{
		GameInstance->SetQuestProgress(QuestProgress);
		GameInstance->SetCurQuestNum(CurQuestNum);

		GameInstance->SetQuests(Quests);

		GameInstance->SetInventory(Controller->GetInventory());
	}
}