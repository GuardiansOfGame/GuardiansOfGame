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
	EIS_InteractObject  UMETA(DisplayName = "InteractObject"),

	EIS_MAX
};

UENUM(BlueprintType)
enum class EMovementStatus : uint8
{
	EMS_Normal			UMETA(DisplayName = "Normal"),
	EMS_Sprinting		UMETA(DisplayName = "Sprinting"),
	EMS_Parkour			UMETA(DisplayName = "Parkour"),
	EMS_Dead			UMETA(DisplayName = "Dead"),

	EMS_MAX
};

UENUM(BlueprintType)
enum class EStaminaStatus : uint8
{
	ESS_Normal					UMETA(DisplayName = "Normal"),
	ESS_BelowMinimum			UMETA(DisplayName = "BelowMinimum"),
	ESS_Exhausted				UMETA(DisplayName = "Exhausted"),
	ESS_ExhaustedRecovering		UMETA(DisplayName = "ExhaustedRecovering"),

	ESS_MAX
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

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Status, meta = (AllowPrivateAccess = "true"))
	EMovementStatus MovementStatus;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Status, meta = (AllowPrivateAccess = "true"))
	EStaminaStatus StaminaStatus;

	UPROPERTY(VisibleAnywhere, Category = Status)
	class UGOGCharacterStatComponent* Stat;

	UPROPERTY(VisibleAnywhere, Category = Status)
	class ANPC* InteractingNPC;

	UPROPERTY(VisibleAnywhere, Category = Status)
	class AItem* InteractingItem;

	UPROPERTY(VisibleAnywhere, Category = Status)
	AActor* InteractingObject;

	UPROPERTY(VisibleAnywhere, Category = Movement)
	float RunningSpeed;

	UPROPERTY(VisibleAnywhere, Category = Movement)
	float SprintingSpeed;

	UPROPERTY(VisibleAnywhere, Category = Movement)
	bool bIsBattling;

	UPROPERTY(VisibleAnywhere, Category = Movement)
	bool bIsRolling;

	UPROPERTY(VisibleAnywhere, Category = Movement)
	bool bIsSliding;

	UPROPERTY(VisibleAnywhere, Category = Movement)
	bool bMovingForward;

	UPROPERTY(VisibleAnywhere, Category = Movement)
	bool bMovingRight;

	UPROPERTY(VisibleAnywhere, Category = Movement)
	bool bShiftKeyDown;

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

	UPROPERTY(VisibleAnywhere, Category = Combat)
	bool bIsAttacking;

	UPROPERTY(VisibleAnywhere, Category = Combat)
	bool bCanNextCombo;

	UPROPERTY(VisibleAnywhere, Category = Combat)
	bool bIsComboInputOn;

	UPROPERTY(VisibleAnywhere, Category = Combat)
	int CurrentComboNum;

	UPROPERTY(VisibleAnywhere, Category = Combat)
	int MaxComboNum;

	UPROPERTY(VisibleAnywhere, Category = Stat)
	float MaxHealth;

	UPROPERTY(VisibleAnywhere, Category = Stat)
	float CurrentHealth;

	UPROPERTY(VisibleAnywhere, Category = Stat)
	float MaxStamina;

	UPROPERTY(VisibleAnywhere, Category = Stat)
	float CurrentStamina;

	UPROPERTY(VisibleAnywhere, Category = Stat)
	float StaminaDrainRate;

	UPROPERTY(VisibleAnywhere, Category = Stat)
	float MinSprintStamina;

	UPROPERTY(VisibleAnywhere, Category = Inventory)
	bool bInventoryOpened;

	UPROPERTY(VisibleAnywhere, Category = Inventory)
	bool bInventoryAnimPlaying;

	UPROPERTY(VisibleAnywhere, Category = Game)
	bool bCanBlockUse;

	UPROPERTY(VisibleAnywhere, Category = Game)
	TArray<bool> UsedBlocks;

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

	void Pause();

	void ShiftKeyDown();
	void ShiftKeyUp();

	void InventoryOnOff();

	void TaskCompleteCheat();

public:
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	FORCEINLINE UGOGCharacterAnimInstance* GetAnimInstance() const { return AnimInstance; }

	FORCEINLINE EInteractionStatus GetInteractionStatus() const { return InteractionStatus; }
	FORCEINLINE void SetInteractionStatus(const EInteractionStatus Status) { InteractionStatus = Status; }

	FORCEINLINE EMovementStatus GetMovementStatus() const { return MovementStatus; }

	FORCEINLINE EStaminaStatus GetStaminaStatus() const { return StaminaStatus; }
	FORCEINLINE void SetStaminaStatus(const EStaminaStatus Status) { StaminaStatus = Status; }

	FORCEINLINE UGOGCharacterStatComponent* GetGOGCharacterStatComponent() const { return Stat; }

	FORCEINLINE ANPC* GetInteractingNPC() const { return InteractingNPC; }
	FORCEINLINE void SetInteractingNPC(ANPC* NPC) { InteractingNPC = NPC; }

	FORCEINLINE AItem* GetInteractingItem() const { return InteractingItem; }
	FORCEINLINE void SetInteractingItem(AItem* Item) { InteractingItem = Item; }

	FORCEINLINE AActor* GetInteractingObject() const { return InteractingObject; }
	FORCEINLINE void SetInteractingObject(AActor* Object) { InteractingObject = Object; }

	FORCEINLINE void SetIsBattling(const bool bValue) { bIsBattling = bValue; }

	FORCEINLINE void SetIsRolling(const bool bValue) { bIsRolling = bValue; }

	FORCEINLINE void SetIsSliding(const bool bValue) { bIsSliding = bValue; }

	FORCEINLINE void SetTargetPosition(const FVector Position) { TargetPosition = Position; }

	FORCEINLINE AWeapon* GetWeapon() const { return Weapon; }

	FORCEINLINE bool GetWeaponEquipped() const { return bWeaponEquipped; }
	FORCEINLINE void SetWeaponEquipped(const bool bValue) { bWeaponEquipped = bValue; }

	FORCEINLINE bool GetCanNextCombo() const { return bCanNextCombo; }
	FORCEINLINE void SetCanNextCombo(const bool bValue) { bCanNextCombo = bValue; }

	FORCEINLINE bool GetIsComboInputOn() const { return bIsComboInputOn; }
	FORCEINLINE void SetIsComboInputOn(const bool bValue) { bIsComboInputOn = bValue; }

	FORCEINLINE int GetCurrentComboNum() const { return CurrentComboNum; }

	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }
	FORCEINLINE float GetCurrentHealth() const { return CurrentHealth; }

	FORCEINLINE float GetMaxStamina() const { return MaxStamina; }
	FORCEINLINE float GetCurrentStamina() const { return CurrentStamina; }

	FORCEINLINE void SetInventoryOpened(const bool bValue) { bInventoryOpened = bValue; }

	FORCEINLINE void SetInventoryAnimPlaying(const bool bValue) { bInventoryAnimPlaying = bValue; }

	FORCEINLINE bool GetCanBlockUse() const { return bCanBlockUse; }
	FORCEINLINE void SetCanBlockUse(const bool bValue) { bCanBlockUse = bValue; }

	FORCEINLINE TArray<bool> GetUsedBlocks() const { return UsedBlocks; }

	void SetMovementStatus(const EMovementStatus Status);

	void UIOn() const;
	void UIOff() const;

	bool CanMove(const float Value) const;

	void SetQuestProgress(const bool bChatEnded = false);

	void EndInteractionWithObject();

	void SwitchLevel(const FName LevelName) const;

	UFUNCTION()
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	void StartComboAttack();
	void EndComboAttack();

	void SetUsedBlocks(const int BlockIndex, const bool bUsed);
};
