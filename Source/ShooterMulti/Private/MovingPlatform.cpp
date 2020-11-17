// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"



AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;
	speed = 40;

	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::AddActiveTrigger()
{
	++ActiveTriggers;
}

void AMovingPlatform::RemoveActiveTrigger()
{
	if(ActiveTriggers>0)
		--ActiveTriggers;
}


void AMovingPlatform::BeginPlay()
{

	Super::BeginPlay();
	if (HasAuthority()) {
		SetReplicates(true);
		SetReplicateMovement(true);
	}
	GlobalStartLocation = GetActorLocation();
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);

}


void AMovingPlatform::Tick(float DeltaTime)
{
	if (ActiveTriggers > 0)
	{

		if (HasAuthority())
		{
			Super::Tick(DeltaTime);


			//only move actor if all triggers are activated

			FVector Location = GetActorLocation();

			FVector NewLocation = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();

			float JourneyLength = (GlobalTargetLocation - GlobalStartLocation).Size();
			float JourneyTravelled = (Location - GlobalStartLocation).Size();

			if (JourneyTravelled >= JourneyLength) {
				//swap destinations
				FVector SwapTemp = GlobalTargetLocation;
				GlobalTargetLocation = GlobalStartLocation;
				GlobalStartLocation = SwapTemp;
				//JourneyTravelled = 0;
			}

			Location += FVector(NewLocation * speed * DeltaTime);

			SetActorLocation(Location);
		}

	}

}
