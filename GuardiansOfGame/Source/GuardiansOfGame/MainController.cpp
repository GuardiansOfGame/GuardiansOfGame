// Fill out your copyright notice in the Description page of Project Settings.

#include "MainController.h"

#include "Main.h"

AMainController::AMainController()
{
}

void AMainController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	Main = Cast<AMain>(InPawn);
}