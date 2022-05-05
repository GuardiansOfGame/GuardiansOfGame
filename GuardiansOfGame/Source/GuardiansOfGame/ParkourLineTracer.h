// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ParkourLineTracer.generated.h"

/**
 * 
 */
UCLASS()
class GUARDIANSOFGAME_API UParkourLineTracer final : public UObject
{
	GENERATED_BODY()

public:
	UParkourLineTracer();

private:
	float MaxJumpHeight;
	float JumpHeight;

	float MaxVaultThick;

	FVector ObstacleLocation;
	FVector ObstacleNormal;
	FVector ObstacleHeight;
	FVector ObstacleLength;

	float ObstacleDistance;

public:
	void CheckObstacle(const class AGOGCharacter* Char);
	void CheckOverObstacle(const AGOGCharacter* Char);
	void CheckObstacleHeight(const AGOGCharacter* Char);
	float CheckObstacleLeft(const AGOGCharacter* Char) const;
	float CheckObstacleRight(const AGOGCharacter* Char) const;
};
