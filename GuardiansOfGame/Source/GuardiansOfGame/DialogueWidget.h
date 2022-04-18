// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogueWidget.generated.h"

/**
 * 
 */
UCLASS()
class GUARDIANSOFGAME_API UDialogueWidget final : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* CanvasPanel;

	UPROPERTY(meta = (BindWidget))
	class UButton* SpeechBubble;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SpeakerName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* DialogueText;

	UPROPERTY(VisibleAnywhere, Category = Dialogue)
	TArray<FString> DialogueStrings;

	UPROPERTY(VisibleAnywhere, Category = Dialogue)
	int DialogueLength;

	UPROPERTY(VisibleAnywhere, Category = Dialogue)
	int DialogueIndex;

protected:
	UFUNCTION()
	void SpeechBubbleClicked();

public:
	void Begin(const TArray<FString> Strings, const FString IName);
	void End() const;

	void SetDialogue();
};
