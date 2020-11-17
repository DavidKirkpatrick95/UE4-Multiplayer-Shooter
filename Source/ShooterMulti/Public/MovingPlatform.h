// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERMULTI_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()
	

protected:


	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

public:

	AMovingPlatform();

	UPROPERTY(EditDefaultsOnly, Category = "Platform")
		float speed;

	UPROPERTY(EditAnywhere, Meta = (MakeEditWidget = true))
		FVector TargetLocation;

	UPROPERTY(EditAnywhere, Meta = (makeEditWidget = true) )
		FVector StartLocation;

	void AddActiveTrigger();

	void RemoveActiveTrigger();


private:

	//global start and end locations

	FVector GlobalStartLocation;
	FVector GlobalTargetLocation;

	UPROPERTY(EditAnywhere)
		int ActiveTriggers = 1;

};
