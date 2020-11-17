// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "MenuInterface.h"
#include "ShooterMultiGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERMULTI_API UShooterMultiGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()

public:
		UShooterMultiGameInstance(const FObjectInitializer& FObjectInitializer);

		void Init();

		UFUNCTION(BlueprintCallable)
			void LoadMenu();

		UFUNCTION(BlueprintCallable)
			void InGameLoadMenu();

		UFUNCTION(Exec)
			void Host();

		UFUNCTION(Exec)
			void Join(const FString& Address);

		UFUNCTION(Exec)
			void LoadMainMenu();

		UFUNCTION(Exec)
			void QuitGame();



private:

	TSubclassOf<class UUserWidget> MenuClass;

	TSubclassOf<class UUserWidget> InGameMenuClass;

	class UMenuWidget* _Menu;

	class UMenuWidget* InGameMenu;

};
