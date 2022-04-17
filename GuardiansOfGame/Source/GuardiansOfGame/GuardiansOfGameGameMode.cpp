// Copyright Epic Games, Inc. All Rights Reserved.

#include "GuardiansOfGameGameMode.h"
#include "GuardiansOfGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGuardiansOfGameGameMode::AGuardiansOfGameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
