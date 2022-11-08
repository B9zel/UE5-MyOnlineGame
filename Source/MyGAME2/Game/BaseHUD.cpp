// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseHUD.h"
#include <MyGAME2/Widgets/StatisticsMenu.h>
#include <MyGAME2/Game_Interface.h>
#include <MyGAME2/Game/BaseGameState.h>
#include <Kismet/GameplayStatics.h>



void ABaseHUD::ToggleHUD(bool isShow)
{
	if (Cast<ABaseGameState>(UGameplayStatics::GetGameState(this))->RoundInProgress)
	{
		if (isShow)
		{
			if (HUDWidget == nullptr)
			{
				HUDWidget = CreateWidget<UGame_Interface>(GetOwningPlayerController(), HUDWidgetClass);
			}
			HUDWidget->AddToViewport();
		}
		else
		{
			HUDWidget->RemoveFromParent();
		}
	}
}

void ABaseHUD::ToggleTab(bool isShow)
{
	if (Cast<ABaseGameState>(UGameplayStatics::GetGameState(this))->RoundInProgress)
	{
		if (isShow)
		{
			if (TabWidget == nullptr)
			{
				TabWidget = CreateWidget<UStatisticsMenu>(GetOwningPlayerController(), TabWidgetClass);
			}
			TabWidget->AddToViewport();
		}
		else
		{
			TabWidget->RemoveFromParent();
		}
	}
}
