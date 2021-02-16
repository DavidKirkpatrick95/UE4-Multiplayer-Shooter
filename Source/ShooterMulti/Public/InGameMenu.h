// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "InGameMenu.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERMULTI_API UInGameMenu : public UMenuWidget
{
	GENERATED_BODY()

public:
	//void SetMenuInterface(IMenuInterface* MenuInterface);



	UFUNCTION()
		void CancelInGameMenu();

	UFUNCTION()
		void QuitToMainMenuLevel();


protected:
	virtual bool Initialize();



	UPROPERTY(meta = (BindWidget))
		class UButton* CancelButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* MainMenuButton;


};
