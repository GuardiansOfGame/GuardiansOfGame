// Fill out your copyright notice in the Description page of Project Settings.

#include "GOGGameInstance.h"

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
}

void UGOGGameInstance::Init()
{
	Super::Init();
}

void UGOGGameInstance::Shutdown()
{
	Super::Shutdown();
}

void UGOGGameInstance::StartGameInstance()
{
	Super::StartGameInstance();
}