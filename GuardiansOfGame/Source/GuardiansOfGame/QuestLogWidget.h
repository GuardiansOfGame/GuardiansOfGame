// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "CustomStruct.h"

#include "QuestLogWidget.generated.h"

/**
 * 
 */
UCLASS()
class GUARDIANSOFGAME_API UQuestLogWidget final : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* VerticalBox;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* QuestName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Task0;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Task1;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Task2;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Task3;

	UPROPERTY(VisibleAnywhere)
	FQuest Quest;

public:
	void Init(const FQuest InputQuest);

	void SetTaskText(UTextBlock* TaskTextBlock, const int TaskNum);
	void UpdateTaskText(const FQuest InputQuest, const int TaskNum);
};
