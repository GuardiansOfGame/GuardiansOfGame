// Fill out your copyright notice in the Description page of Project Settings.


#include "GOGBoss.h"
#include "MonsterAI.h"
#include "AIController.h"
#include "Components/sphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NavigationSystem.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectileBullet.h"
#include "GOGCharacter.h"
#include "GOGMonster.h"
// Sets default values
AGOGBoss::AGOGBoss()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AgroSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AgroSphere"));
	AgroSphere->SetupAttachment(GetRootComponent());
	AgroSphere->InitSphereRadius(700.f);

	CombatSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CombatSphere"));
	CombatSphere->SetupAttachment(GetRootComponent());
	CombatSphere->InitSphereRadius(400.f);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> DieP(TEXT("ParticleSystem'/Game/CustomContent/Monster/Monster713/MonsterEffect/p_bubble_2.p_bubble_2'"));
	if (DieP.Succeeded()) {
		DieParticle = DieP.Object;
	}
}

// Called when the game starts or when spawned
void AGOGBoss::BeginPlay()
{
	Super::BeginPlay();
	
	AIController = Cast<AMonsterAI>(GetController());

	
	AgroSphere->OnComponentBeginOverlap.AddDynamic(this, &AGOGBoss::AgroSphereOnOverlapBegin);
	AgroSphere->OnComponentEndOverlap.AddDynamic(this, &AGOGBoss::AgroSphereOnOverlapEnd);

	AgroSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Ignore);

	CombatSphere->OnComponentBeginOverlap.AddDynamic(this, &AGOGBoss::CombatSphereOnOverlapBegin);
	CombatSphere->OnComponentEndOverlap.AddDynamic(this, &AGOGBoss::CombatSphereOnOverlapEnd);

	CombatSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Ignore);


	MaxHealth = 40.f;
	CurrentHealth = MaxHealth;
}

float AGOGBoss::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	CurrentHealth -= Damage;

	if (CurrentHealth <= 0.0f)
	{
		Die();
	}

	return Damage;
}

// Called every frame
void AGOGBoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGOGBoss::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AGOGBoss::AgroSphereOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		const AGOGCharacter* Char = Cast<AGOGCharacter>(OtherActor);
		if (Char)
		{
			MoveToTarget(Char);
		}
	}
}

void AGOGBoss::AgroSphereOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	const UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	FNavLocation NextLocation;

	if (NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 200.0f, NextLocation))
	{
		AIController->MoveToLocation(NextLocation.Location);
	}
}

void AGOGBoss::CombatSphereOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		const AGOGCharacter* Char = Cast<AGOGCharacter>(OtherActor);
		if (Char)
		{
			Attack();
		}
	}

}

void AGOGBoss::CombatSphereOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void AGOGBoss::MoveToTarget(const AGOGCharacter* Target)
{
	

	if (AIController)
	{
		FAIMoveRequest MoveRequest;
		MoveRequest.SetGoalActor(Target);
		MoveRequest.SetAcceptanceRadius(5.0f);

		FNavPathSharedPtr NavPath;

		AIController->MoveTo(MoveRequest, &NavPath);
	}
}

void AGOGBoss::Attack()
{
	if (ProjectileClass)
	{
		FVector CameraLocation;
		FRotator CameraRotation;
		GetActorEyesViewPoint(CameraLocation, CameraRotation);

		FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);
		FRotator MuzzleRotation = CameraRotation;

		MuzzleRotation.Pitch += 10.0f;
		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();


			AProjectileBullet* Projectile = World->SpawnActor<AProjectileBullet>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (Projectile)
			{
				FVector LaunchDirection = MuzzleRotation.Vector();
				Projectile->BulletDirection(LaunchDirection);
			}
		}
	}
}

void AGOGBoss::Die()
{
	if (DieParticle) {
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DieParticle, GetActorLocation());

	}

	Destroy();
}

