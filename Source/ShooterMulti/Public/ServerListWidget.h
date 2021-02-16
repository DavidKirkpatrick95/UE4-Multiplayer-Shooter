// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ServerListWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERMULTI_API UServerListWidget : public UUserWidget
{
	GENERATED_BODY()

public:



	UFUNCTION()
	void OnClicked();


	UPROPERTY(meta = (BindWidget))
		class UTextBlock* ServerName;


	void Setup(class UMainMenu* Parent, uint32 Index);

	UPROPERTY()
	UMainMenu* Parent;
	
	uint32 Index;

private:

	UPROPERTY(meta = (BindWidget))
		class UButton* ListButton;



};
