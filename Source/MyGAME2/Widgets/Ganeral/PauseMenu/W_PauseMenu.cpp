// Fill out your copyright notice in the Description page of .h"

#include "W_PauseMenu.h"
#include <Components/Button.h>
#include <Components/WidgetSwitcher.h>
#include <Components/VerticalBox.h>
#include <Components/Widget.h>
#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/GameplayStatics.h>
#include <GameFramework/InputSettings.h>
#include <Kismet/KismetInputLibrary.h>
#include "../../../Game/BaseGameInstance.h"
#include "../../../PawnController.h"
#include "../../../Game/BaseHUD.h"





void UW_PauseMenu::NativeConstruct()
{
	Super::NativeConstruct();

	B_FindServer->OnClicked.AddDynamic(this, &UW_PauseMenu::ClickFindServer);
	B_Options->OnClicked.AddDynamic(this, &UW_PauseMenu::ClickOptions);
	B_Quit->OnClicked.AddDynamic(this, &UW_PauseMenu::ClickQuitInMenu);
	B_Play->OnClicked.AddDynamic(this, &UW_PauseMenu::ClickPlay);


	switch (SW_Switch->GetActiveWidgetIndex())
	{
	case 0:
	{
		B_Options->SetIsEnabled(true);
		B_FindServer->SetIsEnabled(false);
		break;
	}
	case 1:
	{
		B_Options->SetIsEnabled(false);
		B_FindServer->SetIsEnabled(true);
		break;
	}
	default:
		break;
	}
	isActive = true;

	SetKeyboardFocus();

	InputSettings = UInputSettings::GetInputSettings();
}

void UW_PauseMenu::NativeDestruct()
{
	Super::NativeDestruct();

	isActive = false;
}


FReply UW_PauseMenu::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	UUserWidget::NativeOnKeyDown(InGeometry, InKeyEvent);

	TArray<FInputActionKeyMapping> ArrAction;
	
	InputSettings->GetActionMappingByName(FName("Escape"), ArrAction);

	for (auto& el : ArrAction)
	{
		if (UKismetInputLibrary::EqualEqual_KeyKey(InKeyEvent.GetKey(), el.Key))
		{
			ClickPlay();
		}
	}
	
	
	return FReply::Handled();
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

void UW_PauseMenu::ClickPlay()
{
	GetOwningPlayer<APawnController>()->SwitchPauseMenu(false);
}

