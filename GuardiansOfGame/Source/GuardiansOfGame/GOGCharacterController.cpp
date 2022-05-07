// Fill out your copyright notice in the Description page of Project Settings.

#include "GOGCharacterController.h"

#include "DialogueWidget.h"
#include "GOGCharacter.h"

AGOGCharacterController::AGOGCharacterController()
{
	static ConstructorHelpers::FClassFinder<UDialogueWidget> DialogueWidgetClassFinder(TEXT("WidgetBlueprint'/Game/Widgets/DialogueWidget_BP.DialogueWidget_BP_C'"));
	if (DialogueWidgetClassFinder.Succeeded())
	{
		DialogueWidgetClass = DialogueWidgetClassFinder.Class;
	}
}

void AGOGCharacterController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	GOGCharacter = Cast<AGOGCharacter>(InPawn);

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