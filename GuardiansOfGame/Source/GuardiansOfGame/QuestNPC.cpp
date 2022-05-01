// Fill out your copyright notice in the Description page of Project Settings.

#include "QuestNPC.h"

#include "GOGCharacter.h"
#include "GOGCharacterStatComponent.h"
#include "GOGGameInstance.h"

AQuestNPC::AQuestNPC()
{
	QuestDialogue.SetNum(MAX_QUEST_NUM);

	UIName = TEXT("QuestNPC");

	const TArray<FString> Give0 = { TEXT("Quest0 Give1"),
 									TEXT("Quest0 Give2") };
	const TArray<FString> Handle0 = { TEXT("Quest0 Handle1"),
									  TEXT("Quest0 Handle2") };
	const TArray<FString> Success0 = { TEXT("Quest0 Success1"),
	 								   TEXT("Quest0 Success2") };
	 
	const TArray<FString> Give1 = { TEXT("Quest1 Give1"),
	 								TEXT("Quest1 Give2") };
	const TArray<FString> Handle1 = { TEXT("Quest1 Handle1"),
									  TEXT("Quest1 Handle2") };
	const TArray<FString> Success1 = { TEXT("Quest1 Success1"),
									   TEXT("Quest1 Success2") };

	QuestDialogue[0] = FDialogueStrings(Give0, Handle0, Success0);
	QuestDialogue[1] = FDialogueStrings(Give1, Handle1, Success1);
}

void AQuestNPC::BeginPlay()
{
	Super::BeginPlay();

	const UGOGGameInstance* GameInstance = Cast<UGOGGameInstance>(GetWorld()->GetGameInstance());
	if(GameInstance)
	{
		const int CurQuestNum = GameInstance->GetCurQuestNum();

		if(GameInstance->GetQuestProgress().QuestAcceptArr[CurQuestNum])
		{
			CurDialogue = QuestDialogue[CurQuestNum].Handle;
		}
		else
		{
			CurDialogue = QuestDialogue[CurQuestNum].Give;
		}
	}
}

void AQuestNPC::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
							   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	AGOGCharacter* Char = Cast<AGOGCharacter>(OtherActor);
	if(Char)
	{
		Char->SetInteractionStatus(EInteractionStatus::EIS_TalkWithNPC);
		Char->SetInteractingNPC(this);

		if(Char->GetGOGCharacterStatComponent()->GetQuestProgress().CurQuestSuccess)
		{
			Char->SetQuestProgress();
		}
	}
}

void AQuestNPC::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
							 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);

	AGOGCharacter* Char = Cast<AGOGCharacter>(OtherActor);
	if(Char)
	{
		Char->SetInteractionStatus(EInteractionStatus::EIS_Normal);
		Char->SetInteractingNPC(nullptr);
	}
}