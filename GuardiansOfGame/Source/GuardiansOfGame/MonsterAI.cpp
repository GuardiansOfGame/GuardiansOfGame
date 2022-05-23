// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAI.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "AI/NavigationSystemBase.h"

void AMonsterAI::BeginPlay()
{
	Super::BeginPlay();

	GoToRandomWaypoint();
}

void AMonsterAI::GoToRandomWaypoint()
{
	FVector Result;
	if (GetRandomPointInRadius(GetPawn()->GetActorLocation(), 600, Result)) {
		MoveToLocation(Result);
	}
}


bool AMonsterAI::GetRandomPointInRadius(const FVector& Origin, float Radius, FVector& OutResult)
{
	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	if (!NavSys)
	{
		return false;
	}

	FVector Result;
	bool bSuccess = NavSys->K2_GetRandomReachablePointInRadius(GetWorld(), Origin, Result, 600);

	//Out
	OutResult = Result;
	return bSuccess;
}

void AMonsterAI::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);

	GoToRandomWaypoint();
}