// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NPC.generated.h"

UCLASS()
class GUARDIANSOFGAME_API ANPC : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANPC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = Mesh)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	UMaterialInterface* Material;

	UPROPERTY(VisibleAnywhere, Category = Collision)
	class UBoxComponent* BoxCollision;

	UPROPERTY(VisibleAnywhere, Category = Widget)
	class UWidgetComponent* KeyWidgetComponent;

	UPROPERTY(VisibleAnywhere, Category = Widget)
	class UKeyWidget* KeyWidget;


protected:
	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
public:
	FORCEINLINE UWidgetComponent* GetKeyWidgetComponent() const { return KeyWidgetComponent; }

	void KeyWidgetOn() const;
};
