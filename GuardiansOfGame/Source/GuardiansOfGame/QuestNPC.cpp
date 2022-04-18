// Fill out your copyright notice in the Description page of Project Settings.

#include "QuestNPC.h"

#include "Main.h"

AQuestNPC::AQuestNPC()
{
	QuestDialogue.SetNum(MAX_QUEST_NUM);

	const FString Name = TEXT("QuestNPC");

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

	QuestDialogue[0] = FDialogueStrings(Name, Give0, Handle0, Success0);
	QuestDialogue[1] = FDialogueStrings(Name, Give1, Handle1, Success1);
}

void AQuestNPC::BeginPlay()
{
	Super::BeginPlay();

}

void AQuestNPC::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
							   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	AMain* Main = Cast<AMain>(OtherActor);
	if(Main)
	{
		Main->SetInteractionStatus(EInteractionStatus::EIS_TalkWithNPC);
		Main->SetInteractingNPC(this);
	}
}

void AQuestNPC::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
							 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);

	AMain* Main = Cast<AMain>(OtherActor);
	if(Main)
	{
		Main->SetInteractionStatus(EInteractionStatus::EIS_Normal);
		Main->SetInteractingNPC(nullptr);
	}
}
