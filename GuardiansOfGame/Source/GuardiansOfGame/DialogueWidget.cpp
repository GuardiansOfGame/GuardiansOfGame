// Fill out your copyright notice in the Description page of Project Settings.

#include "DialogueWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

#include "GOGCharacterController.h"

void UDialogueWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SpeechBubble->OnClicked.AddDynamic(this, &UDialogueWidget::SpeechBubbleClicked);
}

void UDialogueWidget::SpeechBubbleClicked()
{
	if(++DialogueIndex < DialogueLength)
	{
		SetDialogue();
	}
	else
	{
		DialogueIndex = 0;
		SetDialogue();

		End();
	}
}

void UDialogueWidget::Begin(const TArray<FString> Strings, const FString IName)
{
	DialogueStrings = Strings;
	DialogueLength = DialogueStrings.Num();
	DialogueIndex = 0;

	const FText Name = FText::FromString(IName);
	SpeakerName->SetText(Name);

	SetDialogue();
}

void UDialogueWidget::End() const
{
	AGOGCharacterController* Controller = Cast<AGOGCharacterController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if(Controller)
	{
		Controller->EndChat();
	}
}

void UDialogueWidget::SetDialogue()
{
	const FText CurrentText = FText::FromString(DialogueStrings[DialogueIndex]);
	DialogueText->SetText(CurrentText);
}