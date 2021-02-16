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