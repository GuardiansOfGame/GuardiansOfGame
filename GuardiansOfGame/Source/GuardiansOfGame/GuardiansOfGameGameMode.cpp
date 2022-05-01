// Copyright Epic Games, Inc. All Rights Reserved.

#include "GuardiansOfGameGameMode.h"

#include "GOGCharacter.h"
#include "GOGCharacterController.h"

AGuardiansOfGameGameMode::AGuardiansOfGameGameMode()
{
	DefaultPawnClass = AGOGCharacter::StaticClass();
	PlayerControllerClass = AGOGCharacterController::StaticClass();
}