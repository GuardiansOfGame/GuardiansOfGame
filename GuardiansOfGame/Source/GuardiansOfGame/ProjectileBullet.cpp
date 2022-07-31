// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBullet.h"
#include "Engine/Classes/Components/SphereComponent.h"
#include "Engine/Classes/GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GOGCharacter.h"
#include "GOGMonster.h"

// Sets default values
AProjectileBullet::AProjectileBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionComponent = CreateAbstractDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionComponent->InitSphereRadius(15.0f);
	RootComponent = CollisionComponent;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	ProjectileMovementComponent->InitialSpeed = 3000.0f;
	ProjectileMovementComponent->MaxSpeed = 600.0f;

	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.8f;
	ProjectileMovementComponent->Friction = 0.3f;

	Damage = 10.0f;
}

void AProjectileBullet::BulletDirection(const FVector& Direction)
{
	ProjectileMovementComponent->Velocity = Direction * ProjectileMovementComponent->InitialSpeed;
}

// Called when the game starts or when spawned
void AProjectileBullet::BeginPlay()
{
	Super::BeginPlay();

	CollisionComponent->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectileBullet::CollisionComponentOnOverlapBegin);
	CollisionComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Ignore);

	FTimerHandle BulletDestroyTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(BulletDestroyTimerHandle, FTimerDelegate::CreateLambda([&]() {
		Destroy();
	}), 2.0f, false);
}

// Called every frame
void AProjectileBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectileBullet::CollisionComponentOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor) 
	{
		const AGOGCharacter* Char = Cast<AGOGCharacter>(OtherActor);
		if (Char)
		{
			UGameplayStatics::ApplyDamage(OtherActor, Damage, BulletInstigator, this, nullptr);
			Destroy();
		}
	}
}
