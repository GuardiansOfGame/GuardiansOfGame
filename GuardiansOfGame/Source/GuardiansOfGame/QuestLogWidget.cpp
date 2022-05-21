// Fill out your copyright notice in the Description page of Project Settings.

#include "QuestLogWidget.h"

#include "Components/TextBlock.h"

void UQuestLogWidget::Init(const FQuest InputQuest)
{
	Quest = InputQuest;

	QuestName->SetText(Quest.Name);

	SetTaskText(Task0, 0);
	SetTaskText(Task1, 1);
	SetTaskText(Task2, 2);
	SetTaskText(Task3, 3);
}

void UQuestLogWidget::SetTaskText(UTextBlock* TaskTextBlock, const int TaskNum)
{
	if(Quest.Tasks[TaskNum].Type.bIsBattleQuest)
	{
		const int Current = Quest.Tasks[TaskNum].Type.Current;
		const int Goal = Quest.Tasks[TaskNum].Type.Goal;

		const FString TaskString = FString::Printf(TEXT("%s %d/%d"), *(Quest.Tasks[TaskNum].Content.ToString()), Current, Goal);
		TaskTextBlock->SetText(FText::FromString(TaskString));
	}
	else
	{
		TaskTextBlock->SetText(Quest.Tasks[TaskNum].Content);
	}
}
