// Fill out your copyright notice in the Description page of Project Settings.

#include "QuestTester.h"

#include "Components/BoxComponent.h"

#include "GOGCharacter.h"
#include "GOGCharacterStatComponent.h"

// Sets default values
AQuestTester::AQuestTester()
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

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(GetRootComponent());
	BoxCollision->SetBoxExtent(FVector(128.0f, 100.0f, 32.0f));
	BoxCollision->SetRelativeLocation(FVector(0.0f, 82.0f, 33.0f));
	BoxCollision->bHiddenInGame = true;
}

// Called when the game starts or when spawned
void AQuestTester::BeginPlay()
{
	Super::BeginPlay();

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AQuestTester::OnBeginOverlap);
}

void AQuestTester::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const AGOGCharacter* Char = Cast<AGOGCharacter>(OtherActor);
	if(Char && Char->GetGOGCharacterStatComponent())
	{
		Char->GetGOGCharacterStatComponent()->SetCurQuestSuccess(true);

		const int QuestNum = Char->GetGOGCharacterStatComponent()->GetCurQuestNum();
		Char->GetGOGCharacterStatComponent()->SetQuestSuccessArr(QuestNum, true);
	}
}