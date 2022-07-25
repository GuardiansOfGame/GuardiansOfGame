// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GOGMonster.h"
#include "MonsterBullet.generated.h"

class UProjectileMovementComponent;

UCLASS()
class GUARDIANSOFGAME_API AMonsterBullet : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMonsterBullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	void Projectile(float Speed);
protected:
	UProjectileMovementComponent* Bullet;
};