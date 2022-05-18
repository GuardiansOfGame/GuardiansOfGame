// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "QuestDataTable.generated.h"

/**
 * 
 */
class GUARDIANSOFGAME_API QuestDataTable
{
public:
	QuestDataTable();
	~QuestDataTable();
};

USTRUCT(Atomic, BlueprintType)
struct FQuestDataTable : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString QuestName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Task0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Task1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Task2;
};
