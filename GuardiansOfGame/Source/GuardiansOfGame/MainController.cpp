// Fill out your copyright notice in the Description page of Project Settings.

#include "MainController.h"

#include "DialogueWidget.h"
#include "Main.h"

AMainController::AMainController()
{
	static ConstructorHelpers::FClassFinder<UDialogueWidget> DialogueWidgetClassFinder(TEXT("WidgetBlueprint'/Game/Widgets/DialogueWidget_BP.DialogueWidget_BP_C'"));
	if (DialogueWidgetClassFinder.Succeeded())
	{
		DialogueWidgetClass = DialogueWidgetClassFinder.Class;
	}
}

void AMainController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	Main = Cast<AMain>(InPawn);

	if(DialogueWidgetClass)
	{
		DialogueWidget = CreateWidget<UDialogueWidget>(this, DialogueWidgetClass);

		DialogueWidget->AddToViewport();
		DialogueWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AMainController::BeginChat(const TArray<FString> Strings, const FString Name)
{
	const FInputModeGameAndUI InputModeGameAndUI;
	SetInputMode(InputModeGameAndUI);

	bShowMouseCursor = true;

	DialogueWidget->SetVisibility(ESlateVisibility::Visible);
	DialogueWidget->Begin(Strings, Name);
}

void AMainController::EndChat()
{
	const FInputModeGameOnly InputModeGameOnly;
	SetInputMode(InputModeGameOnly);

	bShowMouseCursor = false;

	DialogueWidget->SetVisibility(ESlateVisibility::Hidden);

	Main->SetQuestProgress();
}