// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon.h"

#include "Engine/SkeletalMeshSocket.h"

#include "Main.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> WeaponMesh(TEXT("SkeletalMesh'/Game/Character/Weapon/Hammer/toy_hammer.toy_hammer_toy_hammer'"));
	if (WeaponMesh.Succeeded())
	{
		Mesh->SetSkeletalMesh(WeaponMesh.Object);
	}
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

}

void AWeapon::EquipToBack(const AMain* Main)
{
	if (Main)
	{
		SetInstigator(Main->GetController());

		Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
		Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
		Mesh->SetSimulatePhysics(false);

		const USkeletalMeshSocket* BackSocket = Main->GetMesh()->GetSocketByName("BackSocket");
		if (BackSocket)
		{
			BackSocket->AttachActor(this, Main->GetMesh());
		}
	}
}

void AWeapon::EquipToHand(const AMain* Main)
{
	if(Main)
	{
		SetInstigator(Main->GetController());

		Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
		Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
		Mesh->SetSimulatePhysics(false);

		const USkeletalMeshSocket* RightHandSocket = Main->GetMesh()->GetSocketByName("RightHandSocket");
		if (RightHandSocket)
		{
			RightHandSocket->AttachActor(this, Main->GetMesh());
		}
	}
}
