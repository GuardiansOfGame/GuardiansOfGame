// Copyright Epic Games, Inc. All Rights Reserved.

#include "GuardiansOfGameGameMode.h"

#include "GOGCharacter.h"
#include "GOGCharacterController.h"
#include "UObject/ConstructorHelpers.h"
#include "MenuHUD.h"

AGuardiansOfGameGameMode::AGuardiansOfGameGameMode()
{
	DefaultPawnClass = AGOGCharacter::StaticClass();
	PlayerControllerClass = AGOGCharacterController::StaticClass();

	HUDClass = AMenuHUD::StaticClass();
}