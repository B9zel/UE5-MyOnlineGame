// Fill out your copyright notice in the Description page of .h"

#include "W_PauseMenu.h"
#include <Components/Button.h>
#include <Components/WidgetSwitcher.h>
#include <Components/VerticalBox.h>
#include <Components/Widget.h>
#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/GameplayStatics.h>
#include "../../../Game/BaseGameInstance.h"





void UW_PauseMenu::NativeConstruct()
{
	Super::NativeConstruct();

	B_FindServer->OnClicked.AddDynamic(this, &UW_PauseMenu::ClickFindServer);
	B_Options->OnClicked.AddDynamic(this, &UW_PauseMenu::ClickOptions);
	B_Quit->OnClicked.AddDynamic(this, &UW_PauseMenu::ClickQuitInMenu);


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
	isActive = true;
}

void UW_PauseMenu::NativeDestruct()
{
	Super::NativeDestruct();

	isActive = false;
}


void UW_PauseMenu::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UW_PauseMenu::ClickFindServer()
{
	B_Options->SetIsEnabled(true);
	B_FindServer->SetIsEnabled(false);

	SW_Switch->SetActiveWidgetIndex(0);
}

void UW_PauseMenu::ClickOptions()
{
	B_Options->SetIsEnabled(false);
	B_FindServer->SetIsEnabled(true);

	SW_Switch->SetActiveWidgetIndex(1);
}

void UW_PauseMenu::ClickQuitInMenu()
{
	Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(this))->joinSession(FString("MainLevel"), GetOwningPlayer());
}

