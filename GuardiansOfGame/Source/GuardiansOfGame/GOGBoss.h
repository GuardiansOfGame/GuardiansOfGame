// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "GOGBoss.generated.h"

UCLASS()
class GUARDIANSOFGAME_API AGOGBoss : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGOGBoss();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AI)
	class USphereComponent* AgroSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AI)
	USphereComponent* CombatSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AI)
	class AMonsterAI* AIController;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Particle)
	class UNiagaraSystem* DieParticle;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category = Movement)
	class UAnimMontage* DieMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Sound)
	class USoundCue* BossAttackedSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Sound)
	class USoundCue* BossDieSound;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Sound)
	class USoundCue* BulletSound;

	UPROPERTY(VisibleAnywhere, Category = Stat)
	float MaxHealth;

	UPROPERTY(VisibleAnywhere, Category = Stat)
	float CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bullet)
	FVector MuzzleOffset;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Bullet)
	TSubclassOf<class AProjectileBullet> ProjectileClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
	TSubclassOf<class UMatineeCameraShake> AttackShakeclass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION()
	virtual void AgroSphereOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void AgroSphereOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	virtual void CombatSphereOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void CombatSphereOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void MoveToTarget(const class AGOGCharacter* Target);

	UFUNCTION()
	void Attack();


	void Die();
	
	void CameraShake();

	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }
	FORCEINLINE float GetCurrentHealth() const { return CurrentHealth; }

};