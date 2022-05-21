// Fill out your copyright notice in the Description page of Project Settings.

#include "QuestLogWidget.h"

#include "Components/TextBlock.h"

void UQuestLogWidget::Init(const FQuest InputQuest)
{
	Quest = InputQuest;

	QuestName->SetText(Quest.Name);

	Task0->SetText(Quest.Tasks[0].Content);
	Task1->SetText(Quest.Tasks[1].Content);
	Task2->SetText(Quest.Tasks[2].Content);
	Task3->SetText(Quest.Tasks[3].Content);
}
