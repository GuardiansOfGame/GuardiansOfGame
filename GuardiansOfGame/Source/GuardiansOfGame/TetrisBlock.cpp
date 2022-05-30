// Fill out your copyright notice in the Description page of Project Settings.

#include "TetrisBlock.h"

#include "Kismet/GameplayStatics.h"

#include "GOGCharacter.h"

ATetrisBlock::ATetrisBlock()
{
	BlockNumber = 0;
}

bool ATetrisBlock::UseItem()
{
	AGOGCharacter* Char = Cast<AGOGCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if(Char)
	{
		if(Char->GetCanBlockUse())
		{
			UE_LOG(LogTemp, Warning, TEXT("Use Block"));
			Char->SetUsedBlocks(BlockNumber, true);
			return true;
		}
	}

	return false;
}
