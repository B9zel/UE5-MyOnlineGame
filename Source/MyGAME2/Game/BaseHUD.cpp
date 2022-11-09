// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseHUD.h"
#include <MyGAME2/Widgets/StatisticsMenu.h>
#include <MyGAME2/Game_Interface.h>
#include <MyGAME2/Game/BaseGameState.h>
#include <Kismet/GameplayStatics.h>



ABaseHUD::~ABaseHUD()
{
	HUDWidget = nullptr;
	TabWidget = nullptr;
}

void ABaseHUD::BeginPlay()
{
	Super::BeginPlay();

	//Cast<ABaseGameState>(UGameplayStatics::GetGameState(this))->RoundStarted.AddDynamic(this, &ABaseHUD::CreateHUD);
}

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

void ABaseHUD::CreateHUD()
{
	ToggleHUD(true);
}

UGame_Interface* ABaseHUD::GetHUDWidget()
{
	return HUDWidget;
}
