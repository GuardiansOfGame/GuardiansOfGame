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
	UPROPERTY(EditAnywhere, Category = Mesh)
	class UStaticMeshComponent* OutlineMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Info, meta = (AllowPrivateAccess = "true"))
	int BlockNumber;

protected:
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	virtual bool UseItem() override;
};
