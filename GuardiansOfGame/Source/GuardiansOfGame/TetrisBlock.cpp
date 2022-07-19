// Fill out your copyright notice in the Description page of Project Settings.

#include "TetrisBlock.h"

#include "Kismet/GameplayStatics.h"

#include "GOGCharacter.h"
#include "WarningWidget.h"

ATetrisBlock::ATetrisBlock()
{
	OutlineMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OutlineMesh"));
	OutlineMesh->SetupAttachment(GetRootComponent());

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	if (CubeMesh.Succeeded())
	{
		OutlineMesh->SetStaticMesh(CubeMesh.Object);
	}

	OutlineMesh->SetVisibility(false);

	BlockNumber = 0;
}

void ATetrisBlock::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AItem::OnBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	OutlineMesh->SetVisibility(true);
}

void ATetrisBlock::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AItem::OnEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
	OutlineMesh->SetVisibility(false);
}

bool ATetrisBlock::UseItem()
{
	AGOGCharacter* Char = Cast<AGOGCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if(Char)
	{
		if(Char->GetCanBlockUse())
		{
			Char->SetUsedBlocks(BlockNumber, true);
			return true;
		}
	}

	return false;
}
