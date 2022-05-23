// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class GUARDIANSOFGAME_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(const float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, Category = Mesh)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, Category = Collision)
	class USphereComponent* Collision;

	UPROPERTY(VisibleAnywhere, Category = Widget)
	class UWidgetComponent* KeyWidgetComponent;

	UPROPERTY(VisibleAnywhere, Category = Widget)
	class UKeyWidget* KeyWidget;

protected:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	void KeyWidgetOn() const;
};
