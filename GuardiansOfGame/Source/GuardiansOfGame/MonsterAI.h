// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MonsterAI.generated.h"

/**
 * 
 */
UCLASS()
class GUARDIANSOFGAME_API AMonsterAI : public AAIController
{
	GENERATED_BODY()
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	void GoToRandomWaypoint();
	bool GetRandomPointInRadius(const FVector& Origin, float Radius, FVector& OutResult);
	void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result);

};
