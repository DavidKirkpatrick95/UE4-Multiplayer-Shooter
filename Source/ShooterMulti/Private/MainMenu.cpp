// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "UObject/ConstructorHelpers.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "ServerListWidget.h"





void UMainMenu::SelectIndex(uint32 Index)
{

	SelectedIndex = Index;

}


UMainMenu::UMainMenu(const FObjectInitializer& FObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> ServerListBPClass(TEXT("/Game/Blueprints/MainMenu/WBP_ServerList"));
	if (!ensure(ServerListBPClass.Class != nullptr)) return;

	ServerListClass = ServerListBPClass.Class;


}


bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;
	if (!ensure(HostButton != nullptr)) return false;
	if (!ensure(JoinButton != nullptr)) return false;
	if (!ensure(CancelJoinMenuButton != nullptr)) return false;
	if (!ensure(ConfirmJoinMenuButton != nullptr)) return false;
	if (!ensure(QuitGameButton != nullptr)) return false;
	//if (!ensure(ServerLobbyScrollBox != nullptr)) return false;

	//dynamic event handler

	HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);
	JoinButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);
	CancelJoinMenuButton->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);
	ConfirmJoinMenuButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);
	QuitGameButton->OnClicked.AddDynamic(this, &UMainMenu::QuitGame);

	//HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);

	//ServerLobbyScrollBox->OnClicked.AddDynamic(this, &UMainMenu::Add);





	return true;
}

void UMainMenu::HostServer()
{

	if (MenuInterface != nullptr)
		MenuInterface->Host();

}

void UMainMenu::SetServerList(TArray<FString> ServerNames)
{

	UWorld* World = this->GetWorld();
	if (!ensure(World != nullptr)) return;

	ServerLobbyScrollBox->ClearChildren();
	uint32 i = 0;

	for (const FString& ServerName : ServerNames)
	{


		UServerListWidget* List = CreateWidget<UServerListWidget>(World, ServerListClass);

		if (!ensure(ServerLobbyScrollBox != nullptr)) return;


		List->ServerName->SetText(FText::FromString(ServerName));
		List->Setup(this, i);
		ServerLobbyScrollBox->AddChild(List);
		++i;
		
	}



}


void UMainMenu::JoinServer()
{




	//not using an IP address field anymore

	//const FString& Address = IPAddressField->GetText().ToString();
	if (SelectedIndex.IsSet() && MenuInterface != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Selected index %d"), SelectedIndex.GetValue() );
		MenuInterface->Join(SelectedIndex.GetValue());

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Selected index not set"));

	}



	//	MenuInterface->Join(Address);
	//const FString& Address
}


void UMainMenu::OpenJoinMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(JoinMenu != nullptr)) return;

	MenuSwitcher->SetActiveWidget(JoinMenu);
	if (MenuInterface != nullptr)
	{
		MenuInterface->RefreshServerList();
	}
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

