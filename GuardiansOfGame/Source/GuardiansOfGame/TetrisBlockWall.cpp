// Fill out your copyright notice in the Description page of Project Settings.

#include "TetrisBlockWall.h"

#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"

#include "GOGCharacter.h"
#include "KeyWidget.h"

// Sets default values
ATetrisBlockWall::ATetrisBlockWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> WallMesh(TEXT("StaticMesh'/Game/CustomContent/TetrisBlock/TetrisBlockWall.TetrisBlockWall'"));
	if(WallMesh.Succeeded())
	{
		Mesh->SetStaticMesh(WallMesh.Object);
		Mesh->SetRelativeScale3D(FVector(0.5f));
	}

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(GetRootComponent());
	BoxCollision->SetBoxExtent(FVector(1000.0f, 500.0f, 100.0f));
	BoxCollision->SetRelativeLocation(FVector(-466.0f, -424.0f, -186.0f));
	BoxCollision->SetHiddenInGame(false);

	KeyWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("KeyWidgetComponent"));
	KeyWidgetComponent->SetupAttachment(GetRootComponent());
	KeyWidgetComponent->SetRelativeScale3D(FVector(0.4f));
	KeyWidgetComponent->SetRelativeLocation(FVector(-618.0f, -275.0f, 165.0f));

	static ConstructorHelpers::FClassFinder<UKeyWidget> KeyWidgetAsset(TEXT("WidgetBlueprint'/Game/CustomContent/Widgets/KeyWidget_BP'"));
	if (KeyWidgetAsset.Succeeded())
	{
		KeyWidgetComponent->SetWidgetClass(KeyWidgetAsset.Class);
		KeyWidgetComponent->InitWidget();

		KeyWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	}

	UIName = TEXT("테트리스 블록 벽");
	const TArray<FString> NoticeString = { TEXT("빈 공간에 맞는 블록을 사용하여 벽을 제거하세요.") };
	DialogueStrings = NoticeString;
}

// Called when the game starts or when spawned
void ATetrisBlockWall::BeginPlay()
{
	Super::BeginPlay();

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ATetrisBlockWall::OnBeginOverlap);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &ATetrisBlockWall::OnEndOverlap);

	KeyWidget = Cast<UKeyWidget>(KeyWidgetComponent->GetUserWidgetObject());
}

// Called every frame
void ATetrisBlockWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATetrisBlockWall::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AGOGCharacter* Char = Cast<AGOGCharacter>(OtherActor);
	if(Char)
	{
		PrimaryActorTick.bCanEverTick = true;
		Char->SetCanBlockUse(true);

		Char->SetInteractionStatus(EInteractionStatus::EIS_InteractObject);
		Char->SetInteractingObject(this);

		KeyWidget->PlayAnimation(KeyWidget->GetPopUpAnimaition());
	}
}

void ATetrisBlockWall::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AGOGCharacter* Char = Cast<AGOGCharacter>(OtherActor);
	if (Char)
	{
		PrimaryActorTick.bCanEverTick = false;
		Char->SetCanBlockUse(false);

		Char->SetInteractionStatus(EInteractionStatus::EIS_Normal);
		Char->SetInteractingObject(nullptr);

		KeyWidget->PlayAnimation(KeyWidget->GetPopUpAnimaition(), 0.0f, 1, EUMGSequencePlayMode::Reverse);
	}
}

void ATetrisBlockWall::KeyWidgetOn() const
{
	KeyWidget->PlayAnimation(KeyWidget->GetPopUpAnimaition());
}
