// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterMultiGameInstance.h"

#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

#include "OnlineSessionSettings.h"
//#include "OnlineSubsystemTypes.h"


#include "InGameMenu.h"
#include "MainMenu.h"
#include "MenuWidget.h"

const static FName SESSION_NAME = TEXT("My Session Game");

UShooterMultiGameInstance::UShooterMultiGameInstance(const FObjectInitializer& FObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/Blueprints/MainMenu/WBP_MainMenu"));
	if (!ensure(MenuBPClass.Class != nullptr)) return;

	MenuClass = MenuBPClass.Class;


	ConstructorHelpers::FClassFinder<UUserWidget> InGameMenuBPClass(TEXT("/Game/Blueprints/PauseMenu/WBP_InGameMenu"));
	if (!ensure(InGameMenuBPClass.Class != nullptr)) return;

	InGameMenuClass = InGameMenuBPClass.Class;
	//UE_LOG(LogTemp, Warning, TEXT("Counstructor, Found class %s"), *MenuClass->GetName() );
}

void UShooterMultiGameInstance::Init()
{

	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	//if (!ensure(Subsystem != nullptr)) return;

	if (Subsystem != nullptr)
	{
		//shared pointer to i online session
		SessionInterface = Subsystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{	//UE_LOG(LogTemp, Warning, TEXT("Found session interface"));

			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UShooterMultiGameInstance::OnCreateSessionComplete); //once session has finished completing successfully, then we execute host code
			//SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this);
		}
	}

}

void UShooterMultiGameInstance::LoadMenuWidget()
{
	if (!ensure(MenuClass != nullptr)) return;

	_Menu = CreateWidget<UMainMenu>(this, MenuClass);

	if (!ensure(_Menu != nullptr)) return;

	_Menu->SetUp();

	_Menu->SetMenuInterface(this);

}

void UShooterMultiGameInstance::InGameLoadMenu()
{

	if (!ensure(InGameMenuClass != nullptr)) return;

	UMenuWidget* _Menu = CreateWidget<UMenuWidget>(this, InGameMenuClass);

	if (!ensure(_Menu != nullptr)) return;

	_Menu->SetUp();

	_Menu->SetMenuInterface(this);

	UE_LOG(LogTemp, Warning, TEXT("In Game Load Menu, Found class %s"), *InGameMenuClass->GetName());


}

void UShooterMultiGameInstance::OnCreateSessionComplete(FName SessionName, bool Success)
{

	if (!Success) {
		UE_LOG(LogTemp, Warning, TEXT("session creation no success"));
		return;
	}
	if (_Menu != nullptr)
	{
		_Menu->TearDown();
	}


	UEngine* Engine = GetEngine();
	if (ensure(Engine == nullptr)) return;

	Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Hosting"));

	UWorld* World = GetWorld();
	if (ensure(World == nullptr)) return;
	World->ServerTravel("/Game/Maps/explosive_Barrel_Test?listen");

}


//call when button is clickec
void UShooterMultiGameInstance::Host()
{
	class FOnlineSessionSettings SessionSettings;
	if (SessionInterface.IsValid())
	{
		auto ExistingSession  = SessionInterface->GetNamedSession(SESSION_NAME);
		if (ExistingSession == nullptr) 
		{

			//SessionInterface->DestroySession(SESSION_NAME, );

		}
		else //create session
		{
			SessionInterface->CreateSession(0, SESSION_NAME, SessionSettings); // when host button is pressed, we create the session
		}
	}
}

void UShooterMultiGameInstance::Join(const FString& Address)
{
	if (_Menu != nullptr)
	{
		_Menu->TearDown();
	}

	UEngine* Engine = GetEngine();
	if (ensure(Engine == nullptr)) return;
	Engine->AddOnScreenDebugMessage(0, 5, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (ensure(PlayerController == nullptr)) return;

	PlayerController->ClientTravel(Address,TRAVEL_Absolute);
}

void UShooterMultiGameInstance::LoadMainMenu()
{
	if (_Menu != nullptr)
	{
		_Menu->TearDown();
	}
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (ensure(PlayerController == nullptr)) return;

	PlayerController->ClientTravel("/Game/Maps/MainMenuLevel", TRAVEL_Absolute);

	//UGameplayStatics::OpenLevel(this, "MainMenuLevel");
	//Switch to MainMenuLevel
	//this->LoadMenu();


}

void UShooterMultiGameInstance::QuitGame()
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (ensure(PlayerController == nullptr)) return;

	PlayerController->ConsoleCommand("quit");

}


