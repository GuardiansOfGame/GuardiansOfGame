// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterBullet.h"
#include "Gameframework/ProjectileMovementComponent.h"

// Sets default values
AMonsterBullet::AMonsterBullet()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Bullet = CreateDefaultSubobject<UProjectileMovementComponent>(FName("MonsterBullet"));

	Bullet = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Mesh"));
	

	
}

// Called when the game starts or when spawned
void AMonsterBullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMonsterBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMonsterBullet::Projectile(float Speed)
{
	Bullet->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	Bullet->Activate();
}

