// Fill out your copyright notice in the Description page of Project Settings.

#include "MainAnimInstance.h"

#include "GameFramework/PawnMovementComponent.h"

#include "Main.h"

UMainAnimInstance::UMainAnimInstance()
{
	Main = nullptr;

	Speed = 0.0f;
	bIsInAir = false;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> RollMontageAsset(TEXT("AnimMontage'/Game/Character/Animation/Stand_To_Roll_Montage.Stand_To_Roll_Montage'"));
	if (RollMontageAsset.Succeeded())
	{
		RollMontage = RollMontageAsset.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> VaultMontageAsset(TEXT("AnimMontage'/Game/Character/Animation/Vault_Over_Box_Montage.Vault_Over_Box_Montage'"));
	if (VaultMontageAsset.Succeeded())
	{
		VaultMontage = VaultMontageAsset.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> SlideMontageAsset(TEXT("AnimMontage'/Game/Character/Animation/Running_Slide_Montage.Running_Slide_Montage'"));
	if (SlideMontageAsset.Succeeded())
	{
		SlideMontage = SlideMontageAsset.Object;
	}
}

void UMainAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Main = Cast<AMain>(TryGetPawnOwner());
}

void UMainAnimInstance::NativeUpdateAnimation(const float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if(Main)
	{
		Speed = Main->GetVelocity().Size2D();
		bIsInAir = Main->GetMovementComponent()->IsFalling();
	}
}

void UMainAnimInstance::PlayRollMontage()
{
	Montage_Play(RollMontage);
}

void UMainAnimInstance::PlayVaultMontage(const float ObstacleHeight, const float Left, const float Right)
{
}

void UMainAnimInstance::PlaySlideMontage(const FVector TargetPosition)
{
}

void UMainAnimInstance::AnimNotify_RollStart() const
{
	Main->SetIsRolling(true);
}

void UMainAnimInstance::AnimNotify_RollEnd() const
{
	Main->SetIsRolling(false);
}

void UMainAnimInstance::AnimNotify_VaultEnd() const
{
}