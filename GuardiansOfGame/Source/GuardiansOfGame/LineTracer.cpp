// Fill out your copyright notice in the Description page of Project Settings.

#include "LineTracer.h"

#include "DrawDebugHelpers.h"

#include "Main.h"
#include "MainAnimInstance.h"

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
	const FVector Start = Main->GetActorLocation();
	const FVector End = Start + Main->GetActorForwardVector() * 300.0f;

	FHitResult HitResult{};

	FCollisionQueryParams Params{};
	Params.AddIgnoredActor(Main);

	if (GetWorld())
	{
		bool bTraceResult1 = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_GameTraceChannel1, Params);
		if (bTraceResult1)
		{
			ObstacleLocation = HitResult.Location;
			ObstacleNormal = HitResult.Normal;

			bool bTraceResult2 = GetWorld()->LineTraceSingleByChannel(HitResult, End, ObstacleLocation, ECC_GameTraceChannel1, Params);
			if (bTraceResult2)
			{
				DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1.5f);

				FVector HitEndLocation = HitResult.Location;
				ObstacleLength = HitEndLocation - ObstacleLocation;

				CheckObstacleHeight(Main);
			}
		}
		else
		{
			DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1.5f);
			CheckOverObstacle(Main);
		}
	}
}

void ULineTracer::CheckOverObstacle(const AMain* Main)
{
	
}

void ULineTracer::CheckObstacleHeight(const AMain* Main)
{
	const FVector Start = ObstacleLocation + (ObstacleNormal * -10.0f) + FVector(0.0f, 0.0f, MaxJumpHeight * 3);
	const FVector End = Start - FVector(0.0f, 0.0f, MaxJumpHeight * 3);

	FHitResult HitResult{};

	FCollisionQueryParams Params{};
	Params.AddIgnoredActor(Main);

	if (GetWorld())
	{
		bool bTraceResult = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_GameTraceChannel1, Params);
		if (bTraceResult)
		{
			DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1.5f);

			ObstacleHeight = HitResult.Location;

			JumpHeight = ObstacleHeight.Z - ObstacleLocation.Z;
			if (JumpHeight <= MaxJumpHeight)
			{
				float Left = CheckObstacleLeft(Main);
				float Right = CheckObstacleRight(Main);

				float ObstacleThick = abs(ObstacleLength.Y);
				if (ObstacleThick > 50.0f)
				{
					// TODO: 장애물 위에 올라가는 애니메이션 몽타주 재생하기
					Main->GetMainAnim()->PlayVaultMontage(JumpHeight, Left, Right);
				}
				else
				{
					Main->GetMainAnim()->PlayVaultMontage(JumpHeight, Left, Right);
				}
			}
		}
		else
		{
			DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1.5f);
		}
	}
}

float ULineTracer::CheckObstacleLeft(const AMain* Main) const
{
	return 0.0f;
}

float ULineTracer::CheckObstacleRight(const AMain* Main) const
{
	return 0.0f;
}