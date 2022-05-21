// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CustomStruct.generated.h"

UCLASS()
class GUARDIANSOFGAME_API ACustomStruct final : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACustomStruct();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(const float DeltaTime) override;

};

#define MAX_QUEST_NUM 2
#define TASK_NUM 4

USTRUCT(Atomic, BlueprintType)
struct FDialogueStrings
{
	GENERATED_BODY()

	FDialogueStrings() : Give({}), Handle({}), Success({})
	{}

	FDialogueStrings(const TArray<FString> Give, const TArray<FString> Handle, const TArray<FString> Success)
	{
		this->Give = Give;
		this->Handle = Handle;
		this->Success = Success;
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FString> Give;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FString> Handle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FString> Success;
};

USTRUCT(Atomic, BlueprintType)
struct FQuestBooleans
{
	GENERATED_BODY()

	FQuestBooleans() : CurQuestAccept(false), CurQuestSuccess(false),
					   QuestAcceptArr({}), QuestSuccessArr({})
	{}

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool CurQuestAccept;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool CurQuestSuccess;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<bool> QuestAcceptArr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<bool> QuestSuccessArr;
};

USTRUCT(Atomic, BlueprintType)
struct FQuestType
{
	GENERATED_BODY()

	FQuestType() : bIsBattleQuest(false), Goal(0), Current(0)
	{}

	FQuestType(const bool bIsBattleQuest, const int Goal, const int Current)
	{
		this->bIsBattleQuest = bIsBattleQuest;

		this->Goal = Goal;
		this->Current = Current;
	}

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsBattleQuest;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int Goal;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int Current;
};

USTRUCT(Atomic, BlueprintType)
struct FTask
{
	GENERATED_BODY()

	FTask() : Type(FQuestType()), Content(FText()), bIsCompleted(false)
	{}

	FTask(const FQuestType Type, const FText Content, const bool bIsCompleted)
	{
		this->Type = Type;
		this->Content = Content;
		this->bIsCompleted = bIsCompleted;
	}

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FQuestType Type;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FText Content;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsCompleted;
};

USTRUCT(Atomic, BlueprintType)
struct FQuest
{
	GENERATED_BODY()

	FQuest() : Name(FText()), Tasks({})
	{}

	FQuest(const FText Name, const TArray<FTask> Tasks)
	{
		this->Name = Name;
		this->Tasks = Tasks;
	}

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FText Name;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FTask> Tasks;
};
