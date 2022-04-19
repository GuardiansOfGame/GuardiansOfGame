// Fill out your copyright notice in the Description page of Project Settings.

#include "MainStatComponent.h"

#include "GOGGameInstance.h"

// Sets default values for this component's properties
UMainStatComponent::UMainStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}


// Called when the game starts
void UMainStatComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UMainStatComponent::InitializeComponent()
{
	Super::InitializeComponent();

	Init();
}

void UMainStatComponent::Init()
{
	GameInstance = Cast<UGOGGameInstance>(GEngine->GetWorld()->GetGameInstance());
	if(GameInstance)
	{
		QuestProgress = GameInstance->GetQuestProgress();
		CurQuestNum = GameInstance->GetCurQuestNum();
	}
}

void UMainStatComponent::Save() const
{
	if (GameInstance)
	{
		GameInstance->SetQuestProgress(QuestProgress);
		GameInstance->SetCurQuestNum(CurQuestNum);
	}
}