// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GOGMonster.generated.h"

UENUM(BlueprintType)
enum class EEnemyMovementStatus :uint8
{
	EMS_Idle			 UMETA(DeplayName = "Idle"),
	EMS_MoveToTarget	 UMETA(DeplayName = "MoveToTarget"),
	EMS_Attacking		 UMETA(DeplayName = "Attacking"),

	EMS_Max   UMETA(DeplayName = "DefaultMax")
};

UCLASS()
class GUARDIANSOFGAME_API AGOGMonster : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGOGMonster();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	EEnemyMovementStatus EnemyMovementStatus;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AI)
	class USphereComponent* AgroSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AI)
	USphereComponent* CombatSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AI)
	class AAIController* AIController;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE void SetEnemyMovementStatus(const EEnemyMovementStatus Status) { EnemyMovementStatus = Status; }

	UFUNCTION()
	virtual void AgroSphereOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void AgroSphereOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	virtual void CombatSphereOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void CombatSphereOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void MoveToTarget(const class AGOGCharacter* Target);
};
