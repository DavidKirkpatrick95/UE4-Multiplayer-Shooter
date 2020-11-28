// Fill out your copyright notice in the Description page of Project Settings.

#include "InGameMenu.h"
#include "Components/Button.h"



bool UInGameMenu::Initialize() {

	bool Success = Super::Initialize();
	if (!Success) return false;
	if (!ensure(CancelButton != nullptr)) return false;
	if (!ensure(MainMenuButton != nullptr)) return false;

	//set up dynamic binding with buttons here

	MainMenuButton->OnClicked.AddDynamic(this, &UInGameMenu::QuitToMainMenuLevel);
	CancelButton->OnClicked.AddDynamic(this, &UInGameMenu::CancelInGameMenu);



	return true;
}


void UInGameMenu::SetUp() 
{

	this->AddToViewport();

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (ensure(PlayerController == nullptr)) return;

	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(this->TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	PlayerController->SetInputMode(InputModeData);

	PlayerController->bShowMouseCursor = true;
	this->bIsFocusable = true;


}


void UInGameMenu::TearDown()
{

	this->RemoveFromViewport();

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (ensure(PlayerController == nullptr)) return;

	FInputModeGameOnly InputModeData;
	PlayerController->SetInputMode(InputModeData);

	PlayerController->bShowMouseCursor = false;


}

void UInGameMenu::CancelInGameMenu()
{

	this->TearDown();

}

void UInGameMenu::QuitToMainMenuLevel()
{

	if (MenuInterface != nullptr) {
		TearDown();
		MenuInterface->LoadMainMenu();
	
	}
}