// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/Button.h"
#include "MainMenu.h"
#include "Components/TextBlock.h"

#include "ServerListWidget.h"




void UServerListWidget::OnClicked()
{

	Parent->SelectIndex(Index);
}





void UServerListWidget::Setup(UMainMenu* Parent1, uint32 Index1)
{
	Parent = Parent1;

	Index = Index1;

	//UE_LOG(LogTemp, Warning, TEXT("INDEX OF WIDGET IS %d"), Index);

	ListButton->OnClicked.AddDynamic(this, &UServerListWidget::OnClicked);


}
