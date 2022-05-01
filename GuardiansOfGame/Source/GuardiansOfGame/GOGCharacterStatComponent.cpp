// Fill out your copyright notice in the Description page of Project Settings.

#include "GOGCharacterStatComponent.h"

#include "GOGGameInstance.h"

// Sets default values for this component's properties
UGOGCharacterStatComponent::UGOGCharacterStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}


// Called when the game starts
void UGOGCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UGOGCharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();

	Init();
}

void UGOGCharacterStatComponent::Init()
{
	GameInstance = Cast<UGOGGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		QuestProgress = GameInstance->GetQuestProgress();
		CurQuestNum = GameInstance->GetCurQuestNum();
	}
}

void UGOGCharacterStatComponent::Save() const
{
	if (GameInstance)
	{
		GameInstance->SetQuestProgress(QuestProgress);
		GameInstance->SetCurQuestNum(CurQuestNum);
	}
}