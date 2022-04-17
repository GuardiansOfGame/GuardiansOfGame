// Copyright Epic Games, Inc. All Rights Reserved.

#include "GuardiansOfGameGameMode.h"

#include "Main.h"
#include "MainController.h"

AGuardiansOfGameGameMode::AGuardiansOfGameGameMode()
{
	DefaultPawnClass = AMain::StaticClass();
	PlayerControllerClass = AMainController::StaticClass();
}