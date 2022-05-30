// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TetrisBlockWall.generated.h"

UCLASS()
class GUARDIANSOFGAME_API ATetrisBlockWall final : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATetrisBlockWall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, Category = Mesh)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, Category = Collision)
	class UBoxComponent* BoxCollision;

	UPROPERTY(VisibleAnywhere, Category = Widget)
	class UWidgetComponent* KeyWidgetComponent;

	UPROPERTY(VisibleAnywhere, Category = Widget)
	class UKeyWidget* KeyWidget;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = Dialogue, meta = (AllowPrivateAccess = "true"))
	FString UIName;

	UPROPERTY(VisibleAnywhere, Category = Dialogue)
	TArray<FString> DialogueStrings;

protected:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	FORCEINLINE UWidgetComponent* GetKeyWidgetComponent() const { return KeyWidgetComponent; }

	FORCEINLINE FString GetUIName() const { return UIName; }
	FORCEINLINE TArray<FString> GetDialogueStrings() const { return DialogueStrings; }

	void KeyWidgetOn() const;

	bool CheckCorrectBlockUsed() const;
};
