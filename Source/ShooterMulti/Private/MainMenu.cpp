// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"

bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;
	if (!ensure(HostButton != nullptr)) return false;
	if (!ensure(JoinButton != nullptr)) return false;
	if (!ensure(CancelJoinMenuButton != nullptr)) return false;
	if (!ensure(ConfirmJoinMenuButton != nullptr)) return false;
	if (!ensure(QuitGameButton != nullptr)) return false;

	//dynamic event handler

	HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);
	JoinButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);
	CancelJoinMenuButton->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);
	ConfirmJoinMenuButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);
	QuitGameButton->OnClicked.AddDynamic(this, &UMainMenu::QuitGame);

	return true;
}

void UMainMenu::HostServer()
{

	if (MenuInterface != nullptr)
		MenuInterface->Host();

}

void UMainMenu::JoinServer()
{
	const FString& Address = IPAddressField->GetText().ToString();
	if (MenuInterface != nullptr)
		MenuInterface->Join(Address);
	//const FString& Address
}


void UMainMenu::OpenJoinMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(JoinMenu != nullptr)) return;

	MenuSwitcher->SetActiveWidget(JoinMenu);

}

void UMainMenu::OpenMainMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(JoinMenu != nullptr)) return;

	MenuSwitcher->SetActiveWidget(MainMenu);

}

void UMainMenu::QuitGame()
{

	if (MenuInterface != nullptr)
		MenuInterface->QuitGame();


}

