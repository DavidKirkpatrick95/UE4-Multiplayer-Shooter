// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"

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
			void LoadMenuWidget();

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

		//UFUNCTION(Exec)
		void  OnCreateSessionComplete(FName SessionName, bool Success);
		
		void  OnDestroySessionComplete(FName SessionName, bool Success);

		void  OnFindSessionsComplete(bool Success);

		void CreateSession();


private:

	TSubclassOf<class UUserWidget> MenuClass;

	TSubclassOf<class UUserWidget> InGameMenuClass;

	class UMenuWidget* _Menu;

	class UMenuWidget* InGameMenu;

	IOnlineSessionPtr SessionInterface;

	TSharedPtr<class FOnlineSessionSearch> SessionSearch;
};
