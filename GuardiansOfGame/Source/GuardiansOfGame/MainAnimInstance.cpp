// Fill out your copyright notice in the Description page of Project Settings.

#include "MainAnimInstance.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

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
	Main->SetMovementStatus(EMovementStatus::EMS_Parkour);

	Main->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Main->GetCharacterMovement()->SetMovementMode(MOVE_Flying);

	FVector Location = Main->GetActorLocation();
	Location.Z += ObstacleHeight;
	Main->SetActorLocation(Location);

	FTimerHandle WaitVaultHandle;

	// TODO: 애니메이션 몽타주 (왼쪽 손 : 오른쪽 손) 으로 변경하기
	const float WaitTime = Left > Right ? Montage_Play(VaultMontage) : Montage_Play(VaultMontage);

	GetWorld()->GetTimerManager().SetTimer(WaitVaultHandle, FTimerDelegate::CreateLambda([&]() {
		if (Main)
		{
			Main->SetMovementStatus(EMovementStatus::EMS_Normal);
		}
	}), WaitTime, false);
}

void UMainAnimInstance::PlaySlideMontage(const FVector TargetPosition)
{
	Main->SetMovementStatus(EMovementStatus::EMS_Parkour);
	Main->SetTargetPosition(TargetPosition);
	Main->SetIsSliding(true);

	Main->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	FTimerHandle WaitSlideHandle;
	const float WaitTime = Montage_Play(SlideMontage);

	GetWorld()->GetTimerManager().SetTimer(WaitSlideHandle, FTimerDelegate::CreateLambda([&]() {
		if (Main)
		{
			Main->SetMovementStatus(EMovementStatus::EMS_Normal);
			Main->SetIsSliding(false);

			Main->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			Main->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
		}
	}), WaitTime, false);
}

void UMainAnimInstance::AnimNotify_RollStart() const
{
	Main->SetIsRolling(true);

	Main->GetCameraBoom()->CameraLagSpeed = 5.0f;
}

void UMainAnimInstance::AnimNotify_RollEnd() const
{
	Main->SetIsRolling(false);
}

void UMainAnimInstance::AnimNotify_VaultEnd() const
{
	Main->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Main->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
}