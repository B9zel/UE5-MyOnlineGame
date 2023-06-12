// Fill out your copyright notice in the Description page of Project Settings.


#include "W_MainMenu.h"
#include <Components/Button.h>
#include <Components/WidgetSwitcher.h>
#include <Components/VerticalBox.h>
#include <Components/Widget.h>
#include <Kismet/KismetSystemLibrary.h>
#include "../../Game/BaseGameInstance.h"
#include "W_MainMenuOption.h"


void UW_MainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	B_FindServer->OnClicked.AddDynamic(this, &UW_MainMenu::ClickFindServer);
	B_Options->OnClicked.AddDynamic(this, &UW_MainMenu::ClickOptions);
	B_Quit->OnClicked.AddDynamic(this, &UW_MainMenu::ClickQuit);


	switch (SW_Switch->ActiveWidgetIndex)
	{
	case 0:
		B_Options->SetIsEnabled(true);
		B_FindServer->SetIsEnabled(false);
		break;
	case 1:
		B_Options->SetIsEnabled(false);
		B_FindServer->SetIsEnabled(true);
		break;
	default:
		break;
	}

}

void UW_MainMenu::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UW_MainMenu::ClickFindServer()
{
	B_Options->SetIsEnabled(true);
	B_FindServer->SetIsEnabled(false);

	SW_Switch->SetActiveWidgetIndex(0);
}

void UW_MainMenu::ClickOptions()
{
	B_Options->SetIsEnabled(false);
	B_FindServer->SetIsEnabled(true);

	SW_Switch->SetActiveWidgetIndex(1);
}

void UW_MainMenu::ClickQuit()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Type::Quit, false);
}

