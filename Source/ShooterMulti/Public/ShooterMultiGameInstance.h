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
			void Host() override;

		UFUNCTION(Exec)
			void Join(uint32 Index)  override;

		UFUNCTION(Exec)
			void LoadMainMenu() override;

		UFUNCTION(Exec)
			void QuitGame() override;

		//UFUNCTION(Exec)
		void  OnCreateSessionComplete(FName SessionName, bool Success);
		
		void  OnDestroySessionComplete(FName SessionName, bool Success);

		void  OnFindSessionsComplete(bool Success);

		void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

		//	void BroadcastNetworkFailure(UWorld * World, UNetDriver *NetDriver, ENetworkFailure::Type FailureType, const FString& ErrorString = TEXT(""));

		void OnNetworkFailure(UWorld* World, UNetDriver* NetDriver, ENetworkFailure::Type FailureType, const FString& Error);

		void CreateSession();

		void RefreshServerList() override;


private:

	TSubclassOf<class UUserWidget> MenuClass;

	TSubclassOf<class UUserWidget> InGameMenuClass;

	class UMainMenu* _Menu;

	class UMenuWidget* InGameMenu;

	IOnlineSessionPtr SessionInterface;

	TSharedPtr<class FOnlineSessionSearch> SessionSearch;
};
