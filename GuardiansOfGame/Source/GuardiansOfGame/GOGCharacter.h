// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GOGCharacter.generated.h"

UENUM(BlueprintType)
enum class EInteractionStatus : uint8
{
	EIS_Normal			UMETA(DisplayName = "Normal"),
	EIS_TalkWithNPC		UMETA(DisplayName = "TalkWithNPC"),
	EIS_PickUpItem		UMETA(DisplayName = "PickUpItem"),

	EIS_MAX
};

UENUM(BlueprintType)
enum class EMovementStatus : uint8
{
	EMS_Normal			UMETA(DisplayName = "Normal"),
	EMS_Parkour			UMETA(DisplayName = "Parkour"),

	EMS_MAX
};

UCLASS()
class GUARDIANSOFGAME_API AGOGCharacter final : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGOGCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PostInitializeComponents() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	float BaseLookUpRate;

	UPROPERTY(VisibleAnywhere, Category = Controller)
	class AGOGCharacterController* GOGController;

	UPROPERTY(VisibleAnywhere, Category = Animation)
	class UGOGCharacterAnimInstance* AnimInstance;

	UPROPERTY(VisibleAnywhere, Category = Status)
	EInteractionStatus InteractionStatus;

	UPROPERTY(VisibleAnywhere, Category = Status)
	EMovementStatus MovementStatus;

	UPROPERTY(VisibleAnywhere, Category = Status)
	class UGOGCharacterStatComponent* Stat;

	UPROPERTY(VisibleAnywhere, Category = Status)
	class ANPC* InteractingNPC;

	UPROPERTY(VisibleAnywhere, Category = Movement)
	bool bIsBattling;

	UPROPERTY(VisibleAnywhere, Category = Movement)
	bool bIsRolling;

	UPROPERTY(VisibleAnywhere, Category = Movement)
	bool bIsSliding;

	FVector TargetPosition;

	float RollingInterpSpeed;
	float SlidingInterpSpeed;
	float LagSpeedInterpSpeed;

	UPROPERTY(VisibleAnywhere, Category = Movement)
	class UParkourLineTracer* ParkourLineTracer;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	class UOcclusionChecker* OcclusionChecker;

	UPROPERTY(VisibleAnywhere, Category = Combat)
	class AWeapon* Weapon;

	UPROPERTY(VisibleAnywhere, Category = Combat)
	bool bWeaponEquipped;

protected:
	void MoveForward(const float Value);
	void MoveRight(const float Value);

	void Turn(const float Rate);
	void LookUp(const float Rate);

	void Interaction();

	void SpaceDown();
	void SpaceUp();

	void LCtrlDown();

	void Equip();

	void Attack();

public:
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	FORCEINLINE UGOGCharacterAnimInstance* GetAnimInstance() const { return AnimInstance; }

	FORCEINLINE EInteractionStatus GetInteractionStatus() const { return InteractionStatus; }
	FORCEINLINE void SetInteractionStatus(const EInteractionStatus Status) { InteractionStatus = Status; }

	FORCEINLINE EMovementStatus GetMovementStatus() const { return MovementStatus; }
	FORCEINLINE void SetMovementStatus(const EMovementStatus Status) { MovementStatus = Status; }

	FORCEINLINE UGOGCharacterStatComponent* GetGOGCharacterStatComponent() const { return Stat; }

	FORCEINLINE ANPC* GetInteractingNPC() const { return InteractingNPC; }
	FORCEINLINE void SetInteractingNPC(ANPC* NPC) { InteractingNPC = NPC; }

	FORCEINLINE void SetIsBattling(const bool bValue) { bIsBattling = bValue; }

	FORCEINLINE void SetIsRolling(const bool bValue) { bIsRolling = bValue; }

	FORCEINLINE void SetIsSliding(const bool bValue) { bIsSliding = bValue; }

	FORCEINLINE void SetTargetPosition(const FVector Position) { TargetPosition = Position; }

	FORCEINLINE AWeapon* GetWeapon() const { return Weapon; }

	FORCEINLINE bool GetWeaponEquipped() const { return bWeaponEquipped; }
	FORCEINLINE void SetWeaponEquipped(const bool bValue) { bWeaponEquipped = bValue; }

	void UIOn() const;
	void UIOff() const;

	void SetQuestProgress();

	void SwitchLevel(const FName LevelName) const;
};
