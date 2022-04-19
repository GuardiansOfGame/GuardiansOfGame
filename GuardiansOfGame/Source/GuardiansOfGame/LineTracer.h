// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LineTracer.generated.h"

/**
 * 
 */
UCLASS()
class GUARDIANSOFGAME_API ULineTracer final : public UObject
{
	GENERATED_BODY()

public:
	ULineTracer();

private:
	float MaxJumpHeight;
	float JumpHeight;

	FVector ObstacleLocation;
	FVector ObstacleNormal;
	FVector ObstacleHeight;
	FVector ObstacleLength;

public:
	void CheckObstacle(const class AMain* Main);
	void CheckOverObstacle(const AMain* Main);
	void CheckObstacleHeight(const AMain* Main);
	float CheckObstacleLeft(const AMain* Main) const;
	float CheckObstacleRight(const AMain* Main) const;
};
