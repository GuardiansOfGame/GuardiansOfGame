// Fill out your copyright notice in the Description page of Project Settings.

#include "GOGCharacterController.h"

#include "DialogueWidget.h"
#include "GOGCharacter.h"
#include "GOGCharacterWidget.h"
#include "PauseWidget.h"

AGOGCharacterController::AGOGCharacterController()
{
	static ConstructorHelpers::FClassFinder<UGOGCharacterWidget> GOGCharacterWidgetAsset(TEXT("WidgetBlueprint'/Game/Widgets/GOGCharacterWidget_BP.GOGCharacterWidget_BP_C'"));
	if (GOGCharacterWidgetAsset.Succeeded())
	{
		GOGCharacterWidgetClass = GOGCharacterWidgetAsset.Class;
	}

	static ConstructorHelpers::FClassFinder<UPauseWidget> PauseWidgetAsset(TEXT("WidgetBlueprint'/Game/Widgets/PauseWidget_BP.PauseWidget_BP_C'"));
	if (PauseWidgetAsset.Succeeded())
	{
		PauseWidgetClass = PauseWidgetAsset.Class;
	}

	static ConstructorHelpers::FClassFinder<UDialogueWidget> DialogueWidgetAsset(TEXT("WidgetBlueprint'/Game/Widgets/DialogueWidget_BP.DialogueWidget_BP_C'"));
	if (DialogueWidgetAsset.Succeeded())
	{
		DialogueWidgetClass = DialogueWidgetAsset.Class;
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
}

void AGOGCharacterController::BeginPlay()
{
	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
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

	GOGCharacter->SetQuestProgress();
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
