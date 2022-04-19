// Fill out your copyright notice in the Description page of Project Settings.

#include "LineTracer.h"

#include "DrawDebugHelpers.h"

#include "Main.h"

ULineTracer::ULineTracer()
{
	MaxJumpHeight = 50.0f;
	JumpHeight = 0.0f;

	ObstacleLocation = FVector(0.0f);
	ObstacleNormal = FVector(0.0f);
	ObstacleHeight = FVector(0.0f);
	ObstacleLength = FVector(0.0f);
}

void ULineTracer::CheckObstacle(const AMain* Main)
{
}

void ULineTracer::CheckOverObstacle(const AMain* Main)
{
}

void ULineTracer::CheckObstacleHeight(const AMain* Main)
{
}

float ULineTracer::CheckObstacleLeft(const AMain* Main) const
{
	return 0.0f;
}

float ULineTracer::CheckObstacleRight(const AMain* Main) const
{
	return 0.0f;
}