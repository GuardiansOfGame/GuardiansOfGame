// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "TetrisBlock.generated.h"

/**
 * 
 */
UCLASS()
class GUARDIANSOFGAME_API ATetrisBlock final : public AItem
{
	GENERATED_BODY()

public:
	ATetrisBlock();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Info, meta = (AllowPrivateAccess = "true"))
	int BlockNumber;

public:
	virtual bool UseItem() override;
};
