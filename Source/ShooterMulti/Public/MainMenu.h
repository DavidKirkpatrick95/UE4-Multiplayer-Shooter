// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "MenuInterface.h"

#include "MainMenu.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE();


/**
 * 
 */
UCLASS()
class SHOOTERMULTI_API UMainMenu : public UMenuWidget
{
	GENERATED_BODY()
public:
		UMainMenu(const FObjectInitializer& FObjectInitializer);

		void SetServerList(TArray<FString> ServerNames);

		//void SetMenuInterface(IMenuInterface* MenuInterface);

		void SelectIndex(uint32 Index);


protected:
		virtual bool Initialize();


private:
	UPROPERTY(meta = (BindWidget))
	class UButton* HostButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* JoinButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* CancelJoinMenuButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* ConfirmJoinMenuButton;

	//access thru player controller console commands
	UPROPERTY(meta = (BindWidget))
		class UButton* QuitGameButton;

	UPROPERTY(meta = (BindWidget))
		class UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
		class UWidget* JoinMenu;

	UPROPERTY(meta = (BindWidget))
		class UWidget* MainMenu;

	UPROPERTY()
		class UEditableTextBox* IPAddressField;

	UPROPERTY(meta = (BindWidget))
		class UPanelWidget* ServerLobbyScrollBox;

		//class UScrollBox* ServerLobbyScrollBox;

	TSubclassOf<class UUserWidget> ServerListClass;


	UFUNCTION()
		void HostServer();

	UFUNCTION()
		void JoinServer();

	UFUNCTION()
		void OpenJoinMenu();

	UFUNCTION()
		void OpenMainMenu();

	UFUNCTION()
		void QuitGame();

	TOptional<uint32> SelectedIndex;
};
