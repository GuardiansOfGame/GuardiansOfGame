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

	FDialogueStrings() : Name(""), Give({}), Handle({}), Success({})
	{}

	FDialogueStrings(const FString IName, const TArray<FString> IGive, const TArray<FString> IHandle, const TArray<FString> ISuccess)
	{
		Name = IName;
		Give = IGive;
		Handle = IHandle;
		Success = ISuccess;
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Name;

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

	FQuestBooleans() : CurQAccept(false), CurQSuccess(false),
					   QAcceptArr({}), QSuccessArr({})
	{}

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool CurQAccept;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool CurQSuccess;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<bool> QAcceptArr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<bool> QSuccessArr;
};