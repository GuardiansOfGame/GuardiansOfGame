// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Main.generated.h"

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
class GUARDIANSOFGAME_API AMain final : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMain();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

protected:
	void MoveForward(float Value);
	void MoveRight(float Value);

	void Turn(float Rate);
	void LookUp(float Rate);

	void Interaction();

	void SpaceDown();
	void SpaceUp();

	void LCtrlDown();

public:
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
