// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class GUARDIANSOFGAME_API AWeapon final : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = Mesh)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, Category = Combat)
	AController* WeaponInstigator;

public:
	FORCEINLINE void SetInstigator(AController* Inst) { WeaponInstigator = Inst; }

	void EquipToBack(const class AMain* Main);
	void EquipToHand(const class AMain* Main);
};
