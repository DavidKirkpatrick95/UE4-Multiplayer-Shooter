// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SCritter.generated.h"

class USkeletalMeshComponent;

UCLASS()
class SHOOTERMULTI_API ASCritter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASCritter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Pawn Movement")
	float MaxSpeed;


	void MoveForward(float Value);

	void MoveRight(float Value);

private:

	FVector CurrentVelocity;


};
