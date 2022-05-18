// Fill out your copyright notice in the Description page of Project Settings.

#include "GOGGameInstance.h"

#include "QuestDataTable.h"

UGOGGameInstance::UGOGGameInstance()
{
	MaxQuestNum = MAX_QUEST_NUM;
	CurQuestNum = 0;

	QuestProgress.QuestAcceptArr.SetNum(MaxQuestNum);
	QuestProgress.QuestSuccessArr.SetNum(MaxQuestNum);

	for (int i = 0; i < MaxQuestNum; ++i)
	{
		QuestProgress.QuestAcceptArr[i] = false;
		QuestProgress.QuestSuccessArr[i] = false;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> QuestDataTableAsset(TEXT("DataTable'/Game/DataTable/QuestDataTable.QuestDataTable'"));
	if(QuestDataTableAsset.Succeeded())
	{
		QuestDataTable = QuestDataTableAsset.Object;
	}

	Quests.SetNum(MAX_QUEST_NUM);
	for(int i = 0; i < MAX_QUEST_NUM; ++i)
	{
		Quests[i].Tasks.SetNum(TASK_NUM);
	}
}

void UGOGGameInstance::Init()
{
	Super::Init();

	for(int i = 0; i < MAX_QUEST_NUM; ++i)
	{
		const FQuestDataTable* QuestDataTableRow = QuestDataTable->FindRow<FQuestDataTable>(*FString::FromInt(i + 1), FString(""));
		Quests[i].Name = FText::FromString((*QuestDataTableRow).QuestName);

		Quests[i].Tasks[0].Content = FText::FromString((*QuestDataTableRow).Task0);
		Quests[i].Tasks[1].Content = FText::FromString((*QuestDataTableRow).Task1);
		Quests[i].Tasks[2].Content = FText::FromString((*QuestDataTableRow).Task2);
	}
}

void UGOGGameInstance::Shutdown()
{
	Super::Shutdown();
}

void UGOGGameInstance::StartGameInstance()
{
	Super::StartGameInstance();
}