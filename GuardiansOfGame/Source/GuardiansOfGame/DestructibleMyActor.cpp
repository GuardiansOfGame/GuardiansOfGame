// Fill out your copyright notice in the Description page of Project Settings.


#include "DestructibleMyActor.h"
#include "Engine.h"

// Sets default values
ADestructibleMyActor::ADestructibleMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));

	DestructibleComponent = CreateDefaultSubobject<UDestructibleComponent>(TEXT("Destryctible Component"));
	DestructibleComponent->SetupAttachment(RootComponent);
	DestructibleComponent->SetNotifyRigidBodyCollision(true);

	TriggerComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Component"));
	TriggerComponent->SetupAttachment(RootComponent);
	TriggerComponent->SetHiddenInGame(true);

}

// Called when the game starts or when spawned
void ADestructibleMyActor::BeginPlay()
{
	Super::BeginPlay();
	TriggerComponent->OnComponentBeginOverlap.AddDynamic(this, &ADestructibleMyActor::Trigger);

}

// Called every frame
void ADestructibleMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADestructibleMyActor::Trigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (OtherActor && (OtherActor != this)) {
		Destroy(1000.f, DestructibleComponent->GetComponentLocation(), DestructibleComponent->GetForwardVector(), 1000.f);
	}
	
}
void ADestructibleMyActor::Destroy(float Damage, FVector HitLocation, FVector ImpulseDir, float Impulse)
{

	DestructibleComponent->ApplyDamage(1000.f, HitLocation, ImpulseDir, Impulse);
}
