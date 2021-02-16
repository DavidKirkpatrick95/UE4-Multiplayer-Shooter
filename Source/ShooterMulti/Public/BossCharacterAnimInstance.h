// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BossCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERMULTI_API UBossCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()


		
public:

	virtual void NativeInitializeAnimation() override;


	UFUNCTION(BlueprintCallable, Category = AnimationProperties)
	void UpdateAnimationProperties();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
		float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
		bool bIsInAir;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
		class APawn* Pawn;




};
