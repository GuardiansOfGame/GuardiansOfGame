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

USTRUCT(Atomic, BlueprintType)
struct FDialogueStrings
{
	GENERATED_BODY()

	FDialogueStrings() : Give({}), Handle({}), Success({})
	{}

	FDialogueStrings(const TArray<FString> IGive, const TArray<FString> IHandle, const TArray<FString> ISuccess)
	{
		Give = IGive;
		Handle = IHandle;
		Success = ISuccess;
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FString> Give;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FString> Handle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FString> Success;
};

USTRUCT(BlueprintType)
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