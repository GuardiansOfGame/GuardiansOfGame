// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPC.h"

#include "CustomStruct.h"

#include "QuestNPC.generated.h"

/**
 * 
 */
UCLASS()
class GUARDIANSOFGAME_API AQuestNPC final : public ANPC
{
	GENERATED_BODY()

public:
	AQuestNPC();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = Dialogue, meta = (AllowPrivateAccess = "true"))
	TArray<FDialogueStrings> QuestDialogue;

	UPROPERTY(VisibleAnywhere, Category = Dialogue)
	TArray<FString> CurDialogue;

protected:
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

public:
	FORCEINLINE FDialogueStrings GetQuestDialogue(const int QuestNum) const { return QuestDialogue[QuestNum]; }

	FORCEINLINE TArray<FString> GetCurDialogue() const { return CurDialogue; }
	FORCEINLINE void SetCurDialogue(const TArray<FString> Dialogue) { CurDialogue = Dialogue; }
};
