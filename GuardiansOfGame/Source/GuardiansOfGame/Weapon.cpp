// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon.h"

#include "Components/BoxComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/GameplayStatics.h"

#include "GOGCharacter.h"
#include "GOGMonster.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> WeaponMesh(TEXT("SkeletalMesh'/Game/CustomContent/Weapon/hammer.hammer'"));
	if (WeaponMesh.Succeeded())
	{
		Mesh->SetSkeletalMesh(WeaponMesh.Object);
	}

	CombatCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("CombatCollision"));
	CombatCollision->SetupAttachment(GetRootComponent());
	CombatCollision->SetBoxExtent(FVector(25.0f, 15.0f, 15.0f));
	CombatCollision->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f));
	CombatCollision->bHiddenInGame = true;

	Damage = 20.0f;
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	CombatCollision->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnOverlapBegin);
	DeactiveCollision();
}

void AWeapon::EquipToBack(const AGOGCharacter* Char)
{
	if (Char)
	{
		SetInstigator(Char->GetController());

		Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
		Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
		Mesh->SetSimulatePhysics(false);

		const USkeletalMeshSocket* BackSocket = Char->GetMesh()->GetSocketByName("BackSocket");
		if (BackSocket)
		{
			BackSocket->AttachActor(this, Char->GetMesh());
		}
	}
}

void AWeapon::EquipToHand(const AGOGCharacter* Char)
{
	if(Char)
	{
		SetInstigator(Char->GetController());

		Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
		Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
		Mesh->SetSimulatePhysics(false);

		const USkeletalMeshSocket* RightHandSocket = Char->GetMesh()->GetSocketByName("RightHandSocket");
		if (RightHandSocket)
		{
			RightHandSocket->AttachActor(this, Char->GetMesh());
		}
	}
}

void AWeapon::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, WeaponInstigator, this, nullptr);
	}
}

void AWeapon::ActiveCollision() const
{
	CombatCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void AWeapon::DeactiveCollision() const
{
	CombatCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
