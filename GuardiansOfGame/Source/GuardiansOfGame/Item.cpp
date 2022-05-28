// Fill out your copyright notice in the Description page of Project Settings.

#include "Item.h"

#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"

#include "GOGCharacter.h"
#include "KeyWidget.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	if (CubeMesh.Succeeded())
	{
		Mesh->SetStaticMesh(CubeMesh.Object);
	}

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->SetupAttachment(GetRootComponent());
	Collision->SetSphereRadius(150.0f);
	Collision->bHiddenInGame = false;

	KeyWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("KeyWidgetComponent"));
	KeyWidgetComponent->SetupAttachment(GetRootComponent());
	KeyWidgetComponent->SetRelativeScale3D(FVector(0.4f));
	KeyWidgetComponent->SetRelativeLocation(FVector(-4.0f, 15.0f, 210.0f));

	static ConstructorHelpers::FClassFinder<UKeyWidget> KeyWidgetAsset(TEXT("WidgetBlueprint'/Game/CustomContent/Widgets/KeyWidget_BP.KeyWidget_BP_C'"));
	if(KeyWidgetAsset.Succeeded())
	{
		KeyWidgetComponent->SetWidgetClass(KeyWidgetAsset.Class);
		KeyWidgetComponent->InitWidget();

		KeyWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	}
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnBeginOverlap);
	Collision->OnComponentEndOverlap.AddDynamic(this, &AItem::OnEndOverlap);

	KeyWidget = Cast<UKeyWidget>(KeyWidgetComponent->GetUserWidgetObject());
}

// Called every frame
void AItem::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AGOGCharacter* Char = Cast<AGOGCharacter>(OtherActor);
	if(Char)
	{
		KeyWidget->PlayAnimation(KeyWidget->GetPopUpAnimaition());

		Char->SetInteractionStatus(EInteractionStatus::EIS_PickUpItem);
		Char->SetInteractingItem(this);
	}
}

void AItem::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AGOGCharacter* Char = Cast<AGOGCharacter>(OtherActor);
	if (Char)
	{
		KeyWidget->PlayAnimation(KeyWidget->GetPopUpAnimaition(), 0.0f, 1, EUMGSequencePlayMode::Reverse);

		Char->SetInteractionStatus(EInteractionStatus::EIS_Normal);
		Char->SetInteractingItem(nullptr);
	}
}

void AItem::KeyWidgetOn() const
{
	KeyWidget->PlayAnimation(KeyWidget->GetPopUpAnimaition());
}

void AItem::PickUp()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
}

void AItem::UseItem()
{
}
