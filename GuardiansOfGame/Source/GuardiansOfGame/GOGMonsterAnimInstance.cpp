// Fill out your copyright notice in the Description page of Project Settings.

#include "GOGMonsterAnimInstance.h"

#include "GOGMonster.h"
//UGOGMonsterAnimInstance::UGOGMonsterAnimInstance()
//{
//	EnemyMovementStatus = EEnemyMovementStatus::EMS_Idle;
//}
void UGOGMonsterAnimInstance::NativeInitializeAnimation()
{
	if (!Char)
	{
		Char = TryGetPawnOwner();
		if (Char)
		{
			Monster = Cast<AGOGMonster>(Char);
		}
	}
}

void UGOGMonsterAnimInstance::UpdatedAnimationProperties()
{
	if (!Char)
	{
		Char = TryGetPawnOwner();
		if (Char)
		{
			Monster = Cast<AGOGMonster>(Char);
		}

	}
	if (Char) 
	{
		const FVector Speed = Char->GetVelocity();
		const FVector LateralSpeed = FVector(Speed.X, Speed.Y, 0.f);
		MovementSpeed = LateralSpeed.Size();
	}
}
