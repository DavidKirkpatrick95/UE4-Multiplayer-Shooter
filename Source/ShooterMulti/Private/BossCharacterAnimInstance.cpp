// Fill out your copyright notice in the Description page of Project Settings.


#include "BossCharacterAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"

void UBossCharacterAnimInstance::NativeInitializeAnimation()
{

	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();

	}



}

void UBossCharacterAnimInstance::UpdateAnimationProperties()
{

	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
	}

	if (Pawn)
	{
		FVector Speed = Pawn->GetVelocity();
		FVector LateralSpeed = FVector(Speed.X, Speed.Y, 0.f);
		MovementSpeed = LateralSpeed.Size();

		bIsInAir = Pawn->GetMovementComponent()->IsFalling();
	}



}
