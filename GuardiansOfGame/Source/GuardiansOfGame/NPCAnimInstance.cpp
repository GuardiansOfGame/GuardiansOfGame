// Fill out your copyright notice in the Description page of Project Settings.

#include "NPCAnimInstance.h"

#include "NPC.h"

UNPCAnimInstance::UNPCAnimInstance()
{
	NPC = nullptr;
}

void UNPCAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	NPC = Cast<ANPC>(TryGetPawnOwner());
}