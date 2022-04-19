// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleVolume.h"

#include "Components/BoxComponent.h"

#include "Main.h"

// Sets default values
ABattleVolume::ABattleVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	SetRootComponent(BoxCollision);
	BoxCollision->SetBoxExtent(FVector(500.0f, 500.0f, 32.0f));
	BoxCollision->bHiddenInGame = false;
}

// Called when the game starts or when spawned
void ABattleVolume::BeginPlay()
{
	Super::BeginPlay();

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ABattleVolume::OnBeginOverlap);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &ABattleVolume::OnEndOverlap);
}

void ABattleVolume::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMain* Main = Cast<AMain>(OtherActor);
	if(Main)
	{
		Main->SetIsBattling(true);	
	}
}

void ABattleVolume::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AMain* Main = Cast<AMain>(OtherActor);
	if (Main)
	{
		Main->SetIsBattling(false);
	}
}