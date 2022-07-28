// Fill out your copyright notice in the Description page of Project Settings.

#include "GOGBoss.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "MonsterAI.h"
#include "AIController.h"
#include "Components/sphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NavigationSystem.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectileBullet.h"
#include "Camera/CameraShake.h"
#include "MatineeCameraShake.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"
#include "Sound/SoundCue.h"
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

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> DieP(TEXT("NiagaraSystem'/Game/CustomContent/Monster/Monster713/MonsterEffect/smoke/smoke_FX.smoke_FX'"));
	if (DieP.Succeeded()) {
		DieParticle = DieP.Object;
	}
	static ConstructorHelpers::FClassFinder<UMatineeCameraShake> MyShake(TEXT("Blueprint'/Game/CustomContent/Monster/Monster713/MyShakeCamera'"));
	if (MyShake.Succeeded()) {
		AttackShakeclass = MyShake.Class;
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DieM(TEXT("AnimMontage'/Game/CustomContent/Monster/Boss/boss_Anim_Die_Montage.boss_Anim_Die_Montage'"));
	if (DieM.Succeeded()) {
		DieMontage = DieM.Object;
	}
	static ConstructorHelpers::FObjectFinder<USoundCue> AttackedS(TEXT("SoundCue'/Game/CustomContent/Monster/Monster713/MonsterEffect/sound/GOGBossAttackedSound_Cue.GOGBossAttackedSound_Cue'"));
	if (AttackedS.Succeeded()) {
		BossAttackedSound = AttackedS.Object;
	}
	static ConstructorHelpers::FObjectFinder<USoundCue> DieS(TEXT("SoundCue'/Game/CustomContent/Monster/Monster713/MonsterEffect/sound/GOGBossDieSound_Cue.GOGBossDieSound_Cue'"));
	if (AttackedS.Succeeded()) {
		BossDieSound = DieS.Object;
	}
	static ConstructorHelpers::FObjectFinder<USoundCue> BulletS(TEXT("SoundCue'/Game/CustomContent/Monster/Monster713/MonsterEffect/sound/BulletSound_Cue.BulletSound_Cue'"));
	if (BulletS.Succeeded()) {
		BulletSound = BulletS.Object;
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


	MaxHealth = 30.f;
	CurrentHealth = MaxHealth;
}

float AGOGBoss::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{

	const float Damage = Super::TakeDamage(10, DamageEvent, EventInstigator, DamageCauser);
	CurrentHealth -= Damage;

	if (CurrentHealth <= 0.0f)
	{
		Die();
	}
	/*else if (CurrentHealth == 10.0f) {
		
		this->PlayAnimMontage(DieMontage, 1);
	}*/
	else {
		
		//this->PlayAnimMontage(DieMontage, 3);
		CameraShake();
		UGameplayStatics::PlaySoundAtLocation(this,BossAttackedSound,GetActorLocation());
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
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), DieParticle, GetActorLocation());

	}
	UGameplayStatics::PlaySoundAtLocation(this, BossDieSound, GetActorLocation());
	Destroy();
}

void AGOGBoss::CameraShake()
{
	
	UGameplayStatics::PlayWorldCameraShake(GetWorld(), AttackShakeclass, GetActorLocation(), 800.f, 2500.0f, 1.0f, false);
	//GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(AttackShakeclass, 1.3f);

}

