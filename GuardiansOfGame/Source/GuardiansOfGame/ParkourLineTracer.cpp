// Fill out your copyright notice in the Description page of Project Settings.

#include "ParkourLineTracer.h"

#include "DrawDebugHelpers.h"

#include "GOGCharacter.h"
#include "GOGCharacterAnimInstance.h"

UParkourLineTracer::UParkourLineTracer()
{
	MaxJumpHeight = 50.0f;
	JumpHeight = 0.0f;

	ObstacleLocation = FVector(0.0f);
	ObstacleNormal = FVector(0.0f);
	ObstacleHeight = FVector(0.0f);
	ObstacleLength = FVector(0.0f);
}

void UParkourLineTracer::CheckObstacle(const AGOGCharacter* Char)
{
	const FVector Start = Char->GetActorLocation();
	const FVector End = Start + Char->GetActorForwardVector() * 300.0f;

	FHitResult HitResult{};

	FCollisionQueryParams Params{};
	Params.AddIgnoredActor(Char);

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

				CheckObstacleHeight(Char);
			}
		}
		else
		{
			DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1.5f);
			CheckOverObstacle(Char);
		}
	}
}

void UParkourLineTracer::CheckOverObstacle(const AGOGCharacter* Char)
{
	const FVector Start = Char->GetActorLocation() + FVector(0.0f, 0.0f, 80.0f);
	const FVector End = Start + Char->GetActorForwardVector() * 300.0f;

	FHitResult HitResult{};

	FCollisionQueryParams Params{};
	Params.AddIgnoredActor(Char);

	if (GetWorld())
	{
		bool bTraceResult1 = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_GameTraceChannel1, Params);
		if (bTraceResult1)
		{
			FVector HitLocation = HitResult.Location;

			bool bTraceResult2 = GetWorld()->LineTraceSingleByChannel(HitResult, End, HitLocation, ECC_GameTraceChannel1, Params);
			if (bTraceResult2)
			{
				DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1.5f);

				FVector HitEndLocation = HitResult.Location;
				ObstacleLength = HitEndLocation - HitLocation;

				FVector TargetPosition = Char->GetActorLocation() + Char->GetActorForwardVector() * 250.0f + ObstacleLength;

				Char->GetAnimInstance()->PlaySlideMontage(TargetPosition);
			}
		}
		else
		{
			DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1.5f);
		}
	}
}

void UParkourLineTracer::CheckObstacleHeight(const AGOGCharacter* Char)
{
	const FVector Start = ObstacleLocation + (ObstacleNormal * -10.0f) + FVector(0.0f, 0.0f, MaxJumpHeight * 3);
	const FVector End = Start - FVector(0.0f, 0.0f, MaxJumpHeight * 3);

	FHitResult HitResult{};

	FCollisionQueryParams Params{};
	Params.AddIgnoredActor(Char);

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
				float Left = CheckObstacleLeft(Char);
				float Right = CheckObstacleRight(Char);

				float ObstacleThick = abs(ObstacleLength.Size());
				if (ObstacleThick > 50.0f)
				{
					Char->GetAnimInstance()->PlayClimbMontage(JumpHeight);
				}
				else
				{
					Char->GetAnimInstance()->PlayVaultMontage(JumpHeight, Left, Right);
				}
			}
		}
		else
		{
			DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1.5f);
		}
	}
}

float UParkourLineTracer::CheckObstacleLeft(const AGOGCharacter* Char) const
{
	const FVector Start = ObstacleLocation + (ObstacleNormal * -10.0f) + Char->GetActorRightVector() * -150.0f;
	const FVector End = Start - Char->GetActorRightVector() * -150.0f;

	FHitResult HitResult{};

	FCollisionQueryParams Params{};
	Params.AddIgnoredActor(Char);

	if (GetWorld())
	{
		bool bTraceResult = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_GameTraceChannel1, Params);
		if (bTraceResult)
		{
			DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1.5f);
		}
		else
		{
			DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1.5f);
		}
	}

	return (HitResult.Location - End).Size();
}

float UParkourLineTracer::CheckObstacleRight(const AGOGCharacter* Char) const
{
	const FVector Start = ObstacleLocation + (ObstacleNormal * -10.0f) + Char->GetActorRightVector() * 150.0f;
	const FVector End = Start - Char->GetActorRightVector() * 150.0f;

	FHitResult HitResult{};

	FCollisionQueryParams Params{};
	Params.AddIgnoredActor(Char);

	if (GetWorld())
	{
		bool bTraceResult = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_GameTraceChannel1, Params);
		if (bTraceResult)
		{
			DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1.5f);
		}
		else
		{
			DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1.5f);
		}
	}

	return (End - HitResult.Location).Size();
}
