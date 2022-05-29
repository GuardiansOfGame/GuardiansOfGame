// Fill out your copyright notice in the Description page of Project Settings.

#include "GOGCharacterController.h"

#include "DialogueWidget.h"
#include "GOGCharacter.h"
#include "GOGCharacterStatComponent.h"
#include "GOGGameInstance.h"
#include "GOGCharacterWidget.h"
#include "HealthBar.h"
#include "PauseWidget.h"
#include "QuestLogWidget.h"

AGOGCharacterController::AGOGCharacterController()
{
	static ConstructorHelpers::FClassFinder<UGOGCharacterWidget> GOGCharacterWidgetAsset(TEXT("WidgetBlueprint'/Game/CustomContent/Widgets/GOGCharacterWidget_BP.GOGCharacterWidget_BP_C'"));
	if (GOGCharacterWidgetAsset.Succeeded())
	{
		GOGCharacterWidgetClass = GOGCharacterWidgetAsset.Class;
	}

	static ConstructorHelpers::FClassFinder<UPauseWidget> PauseWidgetAsset(TEXT("WidgetBlueprint'/Game/CustomContent/Widgets/PauseWidget_BP.PauseWidget_BP_C'"));
	if (PauseWidgetAsset.Succeeded())
	{
		PauseWidgetClass = PauseWidgetAsset.Class;
	}

	static ConstructorHelpers::FClassFinder<UDialogueWidget> DialogueWidgetAsset(TEXT("WidgetBlueprint'/Game/CustomContent/Widgets/DialogueWidget_BP.DialogueWidget_BP_C'"));
	if (DialogueWidgetAsset.Succeeded())
	{
		DialogueWidgetClass = DialogueWidgetAsset.Class;
	}

	static ConstructorHelpers::FClassFinder<UHealthBar> MonsterHealthWidgetAsset(TEXT("WidgetBlueprint'/Game/CustomContent/Widgets/HealthBar_BP.HealthBar_BP_C'"));
	if (MonsterHealthWidgetAsset.Succeeded())
	{
		MonsterHealthWidgetClass = MonsterHealthWidgetAsset.Class;
	}
}

void AGOGCharacterController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	GOGCharacter = Cast<AGOGCharacter>(InPawn);

	if(GOGCharacterWidgetClass)
	{
		GOGCharacterWidget = CreateWidget<UGOGCharacterWidget>(this, GOGCharacterWidgetClass);

		SetHealthBarPercent(GOGCharacter->GetCurrentHealth(), GOGCharacter->GetMaxHealth());
		SetStaminaBarPercent(GOGCharacter->GetCurrentStamina(), GOGCharacter->GetMaxStamina());

		GOGCharacterWidget->AddToViewport();
		GOGCharacterWidget->GetQuestLogWidget()->SetVisibility(ESlateVisibility::Hidden);
	}

	if (PauseWidgetClass)
	{
		PauseWidget = CreateWidget<UPauseWidget>(this, PauseWidgetClass);
	}

	if (DialogueWidgetClass)
	{
		DialogueWidget = CreateWidget<UDialogueWidget>(this, DialogueWidgetClass);

		DialogueWidget->AddToViewport();
		DialogueWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	if(MonsterHealthWidgetClass)
	{
		MonsterHealthWidget = CreateWidget<UHealthBar>(this, MonsterHealthWidgetClass);

		MonsterHealthWidget->AddToViewport();
		MonsterHealthWidget->SetVisibility(ESlateVisibility::Hidden);

		const FVector2D Alignment(0.0f, 0.0f);
		MonsterHealthWidget->SetAlignmentInViewport(Alignment);
	}
}

void AGOGCharacterController::BeginPlay()
{
	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;

	const UGOGCharacterStatComponent* StatComponent = GOGCharacter->GetGOGCharacterStatComponent();
	const int CurQuestNum = StatComponent->GetCurQuestNum();

	if(CurQuestNum == MAX_QUEST_NUM)
	{
		return;
	}

	if(StatComponent)
	{
		InitQuestLog(StatComponent, CurQuestNum);

		const bool QuestAccept = StatComponent->GetQuestProgress().CurQuestAccept;
		const bool QuestSuccess = StatComponent->GetQuestProgress().CurQuestSuccess;

		if(CurQuestNum == MAX_QUEST_NUM && QuestSuccess)
		{
			SetQuestLogVisibillity(StatComponent, true);
			return;
		}

		if(QuestAccept)
		{
			SetQuestLogVisibillity(StatComponent);
		}
	}
}

void AGOGCharacterController::BeginChat(const TArray<FString> Strings, const FString Name)
{
	const FInputModeGameAndUI InputModeGameAndUI;
	SetInputMode(InputModeGameAndUI);

	bShowMouseCursor = true;

	DialogueWidget->SetVisibility(ESlateVisibility::Visible);
	DialogueWidget->Begin(Strings, Name);
}

void AGOGCharacterController::EndChat()
{
	const FInputModeGameOnly InputModeGameOnly;
	SetInputMode(InputModeGameOnly);

	bShowMouseCursor = false;

	DialogueWidget->SetVisibility(ESlateVisibility::Hidden);

	GOGCharacter->SetQuestProgress(true);
}

void AGOGCharacterController::TogglePause(const bool bPause)
{
	if(bPause)
	{
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;

		SetPause(true);

		PauseWidget->AddToViewport();
		PauseWidget->PlayPopUpAnimation(false);
	}
	else
	{
		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;

		SetPause(false);

		PauseWidget->PlayPopUpAnimation(true);

		FTimerHandle UIAnimDelayTimerHandle;
		GetWorld()->GetTimerManager().SetTimer(UIAnimDelayTimerHandle, FTimerDelegate::CreateLambda([&]() {
			PauseWidget->RemoveFromParent();
		}), 0.25f, false);
	}
}

void AGOGCharacterController::SetHealthBarPercent(const float CurrentHealth, const float MaxHealth) const
{
	GOGCharacterWidget->SetHealthBarPercent(CurrentHealth, MaxHealth);
}

void AGOGCharacterController::SetStaminaBarPercent(const float CurrentStamina, const float MaxStamina) const
{ 
	GOGCharacterWidget->SetStaminaBarPercent(CurrentStamina, MaxStamina);
}

void AGOGCharacterController::SetStaminaBarColor(const EStaminaStatus Status) const
{
	GOGCharacterWidget->SetStaminaBarColor(Status);
}

void AGOGCharacterController::ToggleInventory(const bool bVisible)
{
	if(bVisible)
	{
		SetInputMode(FInputModeGameAndUI());
		bShowMouseCursor = true;

		GOGCharacter->SetInventoryOpened(true);
		GOGCharacter->SetInventoryAnimPlaying(true);

		GOGCharacterWidget->ViewInventory();

		FTimerHandle UIAnimDelayTimerHandle;
		GetWorld()->GetTimerManager().SetTimer(UIAnimDelayTimerHandle, FTimerDelegate::CreateLambda([&]() {
			GOGCharacter->SetInventoryAnimPlaying(false);
		}), 0.3f, false);
	}
	else
	{
		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;

		GOGCharacter->SetInventoryOpened(false);
		GOGCharacter->SetInventoryAnimPlaying(true);

		GOGCharacterWidget->HideInventory();

		FTimerHandle UIAnimDelayTimerHandle;
		GetWorld()->GetTimerManager().SetTimer(UIAnimDelayTimerHandle, FTimerDelegate::CreateLambda([&]() {
			GOGCharacter->SetInventoryAnimPlaying(false);
		}), 0.3f, false);
	}
}

void AGOGCharacterController::InitQuestLog(const class UGOGCharacterStatComponent* StatComponent, const int CurQuestNum) const
{
	GOGCharacterWidget->InitQuestLog(StatComponent->GetQuests()[CurQuestNum]);
}

void AGOGCharacterController::UpdateQuestLog(UGOGCharacterStatComponent* StatComponent, const int TaskNum) const
{
	const int CurQuestNum = StatComponent->GetCurQuestNum();
	const FQuest CurQuest = StatComponent->GetQuests()[CurQuestNum];

	bool bCompletedAllTasks = false;

	for(int i = 0; i < TASK_NUM; ++i)
	{
		bCompletedAllTasks = CurQuest.Tasks[i].bIsCompleted;
		if(!bCompletedAllTasks)
		{
			break;
		}
	}

	if(bCompletedAllTasks)
	{
		StatComponent->SetCurQuestSuccess(true);
		StatComponent->SetQuestSuccessArr(CurQuestNum, true);
	}

	GOGCharacterWidget->GetQuestLogWidget()->UpdateTaskText(CurQuest, TaskNum);
}

void AGOGCharacterController::SetQuestLogVisibillity(const class UGOGCharacterStatComponent* StatComponent, const bool bForceHidden) const
{
	if (bForceHidden)
	{
		GOGCharacterWidget->GetQuestLogWidget()->SetVisibility(ESlateVisibility::Hidden);
		return;
	}

	const bool QuestAccept = StatComponent->GetQuestProgress().CurQuestAccept;
	if (QuestAccept)
	{
		GOGCharacterWidget->GetQuestLogWidget()->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		GOGCharacterWidget->GetQuestLogWidget()->SetVisibility(ESlateVisibility::Hidden);
	}
}
