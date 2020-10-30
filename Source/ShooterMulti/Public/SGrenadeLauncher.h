// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SWeapon.h"
#include "SGrenadeLauncher.generated.h"

class AActor;

/**
 * 
 */
UCLASS()
class SHOOTERMULTI_API ASGrenadeLauncher : public ASWeapon
{
	GENERATED_BODY()
	

protected:



	UPROPERTY(EditDefaultsOnly, Category = "GrenadeLauncher")
		TSubclassOf<class AActor> ProjectileClass;

	//UFUNCTION(BlueprintCallable, Category = "Weapon")
		virtual void Fire() override;

};
