// Fill out your copyright notice in the Description page of Project Settings.

#include "GOGMonster.h"
#include "MonsterAI.h"
#include "AIController.h"
#include "Components/sphereComponent.h"
#include "Engine/Classes/Particles/ParticleSystem.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NavigationSystem.h"
#include "ProjectileBullet.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "GOGCharacter.h"
#include "GOGCharacterController.h"

// Sets default values
AGOGMonster::AGOGMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AgroSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AgroSphere"));
	AgroSphere->SetupAttachment(GetRootComponent());
	AgroSphere->InitSphereRadius(800.f);

	CombatSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CombatSphere"));
	CombatSphere->SetupAttachment(GetRootComponent());
	CombatSphere->InitSphereRadius(400.f);
	

	MaxHealth = 40.f;
	CurrentHealth = MaxHealth;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> DieP(TEXT("ParticleSystem'/Game/CustomContent/Monster/Monster713/MonsterEffect/p_bubble_2.p_bubble_2'"));
	if (DieP.Succeeded()) {
		DieParticle = DieP.Object;
	}
	static ConstructorHelpers::FObjectFinder<USoundCue> DieS(TEXT("SoundCue'/Game/CustomContent/Monster/Monster713/MonsterEffect/sound/GOGMonsterHitSound_Cue.GOGMonsterHitSound_Cue'"));
	if (DieS.Succeeded()) {
		MonsterHitSound = DieS.Object;
	}
	static ConstructorHelpers::FObjectFinder<USoundCue> BulletS(TEXT("SoundCue'/Game/CustomContent/Monster/Monster713/MonsterEffect/sound/BulletSound_Cue.BulletSound_Cue'"));
	if (BulletS.Succeeded()) {
		BulletSound = BulletS.Object;
	}
}

// Called when the game starts or when spawned
void AGOGMonster::BeginPlay()
{
	Super::BeginPlay();

	AIController = Cast<AMonsterAI>(GetController());

	AgroSphere->OnComponentBeginOverlap.AddDynamic(this, &AGOGMonster::AgroSphereOnOverlapBegin);
	AgroSphere->OnComponentEndOverlap.AddDynamic(this, &AGOGMonster::AgroSphereOnOverlapEnd);

	AgroSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Ignore);

	CombatSphere->OnComponentBeginOverlap.AddDynamic(this, &AGOGMonster::CombatSphereOnOverlapBegin);
	CombatSphere->OnComponentEndOverlap.AddDynamic(this, &AGOGMonster::CombatSphereOnOverlapEnd);

	//CombatSphere->SetCollisionEnabled(ECollisionEnabled::);
	//CombatSphere->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	//CombatSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	CombatSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Ignore);
}

float AGOGMonster::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	CurrentHealth -= Damage;

	if(CurrentHealth <= 0.0f)
	{
		const AGOGCharacterController* GOGController = Cast<AGOGCharacterController>(EventInstigator);
		AGOGCharacter* Char = Cast<AGOGCharacter>(GOGController->GetCharacter());

		if(GOGController && Char)
		{
			if(Char)
			{
				Char->KillMonster(1);
			}
		}

		Die();
	}

	return Damage;
}

// Called every frame
void AGOGMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AGOGMonster::SetEnemyMovementStatus(const EEnemyMovementStatus Status)
{
	EnemyMovementStatus = Status;
}

void AGOGMonster::AgroSphereOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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

void AGOGMonster::AgroSphereOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	const UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	FNavLocation NextLocation;

	if(NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 200.0f, NextLocation))
	{
		AIController->MoveToLocation(NextLocation.Location);
	}
}

void AGOGMonster::CombatSphereOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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

void AGOGMonster::CombatSphereOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void AGOGMonster::MoveToTarget(const AGOGCharacter* Target)
{
	SetEnemyMovementStatus(EEnemyMovementStatus::EMS_MoveToTarget);

	if (AIController) 
	{
		FAIMoveRequest MoveRequest;
		MoveRequest.SetGoalActor(Target);
		MoveRequest.SetAcceptanceRadius(5.0f);

		FNavPathSharedPtr NavPath;

		AIController->MoveTo(MoveRequest, &NavPath);
	}
}


void AGOGMonster::Attack()
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
				UGameplayStatics::PlaySoundAtLocation(this, BulletSound, GetActorLocation());
			}
		}
	}

}

void AGOGMonster::Die()
{
	UGameplayStatics::PlaySoundAtLocation(this, MonsterHitSound, GetActorLocation());
	
	if (DieParticle) {
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DieParticle, GetActorLocation());
	}
	
	Destroy();
}
