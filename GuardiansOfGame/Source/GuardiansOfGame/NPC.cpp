// Fill out your copyright notice in the Description page of Project Settings.

#include "NPC.h"

#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"

#include "KeyWidget.h"
#include "Main.h"

// Sets default values
ANPC::ANPC()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> NPCMesh(TEXT("SkeletalMesh'/Game/Character/ybot/ybot.ybot'"));
	if (NPCMesh.Succeeded())
	{
		Mesh->SetSkeletalMesh(NPCMesh.Object);
		Mesh->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

		if (Mesh->GetMaterial(0))
		{
			static ConstructorHelpers::FObjectFinder<UMaterialInterface> PurpleMaterialAsset(TEXT("Material'/Game/Character/ybot/Alpha_Body_MAT1.Alpha_Body_MAT1'"));
			if (PurpleMaterialAsset.Succeeded())
			{
				UMaterialInterface* PurpleMaterial = PurpleMaterialAsset.Object;
				Mesh->SetMaterial(0, PurpleMaterial);
			}
		}
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> NPCAnimInstance(TEXT("AnimBlueprint'/Game/Character/NPCAnimation/NPCAnimInstance_BP.NPCAnimInstance_BP_C'"));
	if (NPCAnimInstance.Succeeded())
	{
		Mesh->SetAnimInstanceClass(NPCAnimInstance.Class);
	}

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(GetRootComponent());
	BoxCollision->SetBoxExtent(FVector(128.0f, 100.0f, 32.0f));
	BoxCollision->SetRelativeLocation(FVector(0.0f, 82.0f, 33.0f));

	KeyWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("KeyWidgetComponent"));
	KeyWidgetComponent->SetupAttachment(GetRootComponent());
	KeyWidgetComponent->SetRelativeScale3D(FVector(0.4f));
	KeyWidgetComponent->SetRelativeLocationAndRotation(FVector(-4.0f, 15.0f, 200.0f), FRotator(0.0f, 90.0f, 0.0f));

	static ConstructorHelpers::FClassFinder<UKeyWidget> KeyWidgetAsset(TEXT("WidgetBlueprint'/Game/Widgets/KeyWidget_BP.KeyWidget_BP_C'"));
	if(KeyWidgetAsset.Succeeded())
	{
		KeyWidgetComponent->SetWidgetClass(KeyWidgetAsset.Class);
		KeyWidgetComponent->InitWidget();

		KeyWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	}
}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ANPC::OnBeginOverlap);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &ANPC::OnEndOverlap);

	KeyWidget = Cast<UKeyWidget>(KeyWidgetComponent->GetUserWidgetObject());
}

void ANPC::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						  int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const AMain* Main = Cast<AMain>(OtherActor);
	if(Main)
	{
		KeyWidget->PlayAnimation(KeyWidget->GetPopUpAnimaition());
	}
}

void ANPC::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex)
{
	const AMain* Main = Cast<AMain>(OtherActor);
	if (Main)
	{
		KeyWidget->PlayAnimation(KeyWidget->GetPopUpAnimaition(), 0.0f, 1, EUMGSequencePlayMode::Reverse);
	}
}