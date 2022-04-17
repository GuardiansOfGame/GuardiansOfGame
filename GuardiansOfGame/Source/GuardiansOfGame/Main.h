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
	virtual void Tick(const float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	float BaseLookUpRate;

protected:
	void MoveForward(const float Value);
	void MoveRight(const float Value);

	void Turn(const float Rate);
	void LookUp(const float Rate);

	void Interaction();

	void SpaceDown();
	void SpaceUp();

	void LCtrlDown();

public:
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
