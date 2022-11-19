// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseHUD.h"
#include <MyGAME2/Widgets/StatisticsMenu.h>
#include <MyGAME2/Game_Interface.h>
#include <MyGAME2/Game/BaseGameState.h>
#include <Kismet/GameplayStatics.h>
#include <MyGAME2/Game/PlayerStatistic.h>
#include <MyGAME2/Widgets/W_Spectator.h>
//#include <GameFramework/PlayerController.h>


ABaseHUD::~ABaseHUD()
{
	HUDWidget = nullptr;
	TabWidget = nullptr;
}

void ABaseHUD::BeginPlay()
{
	Super::BeginPlay();

	Cast<ABaseGameState>(UGameplayStatics::GetGameState(this))->RoundStarted.AddDynamic(this, &ABaseHUD::OnRoundStarted);
}

void ABaseHUD::ToggleHUD(bool isShow)
{
	
	if (isShow)
	{
		if (Cast<APlayerStatistic>(GetOwningPlayerController()->GetPlayerState<APlayerStatistic>())->isAlive)
		{
			if (HUDWidget == nullptr)
			{
				HUDWidget = CreateWidget<UGame_Interface>(GetOwningPlayerController(), HUDWidgetClass);
			}
			HUDWidget->AddToViewport();
		}
	}
	else
	{
		if (HUDWidget != nullptr)
		{
			HUDWidget->RemoveFromParent();
			HUDWidget = nullptr;
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
			if (TabWidget != nullptr)
			{
				TabWidget->RemoveFromParent();
				TabWidget = nullptr;
			}
		}
	}
}

void ABaseHUD::ToggleSpectatorHUD(bool isShow)
{
	if (Cast<ABaseGameState>(UGameplayStatics::GetGameState(this))->RoundInProgress)
	{
		if (isShow)
		{
			if (SpectatorWidget == nullptr)
			{
				SpectatorWidget = CreateWidget<UW_Spectator>(GetOwningPlayerController(), SpectatorWidgetClass);
			}
			SpectatorWidget->AddToViewport();
		}
		else
		{
			if (SpectatorWidget != nullptr)
			{
				SpectatorWidget->RemoveFromParent();
				SpectatorWidget = nullptr;
			}
		}
	}
}

void ABaseHUD::OnRoundStarted()
{
	APlayerStatistic* PlayerState = GetOwningPlayerController()->GetPlayerState<APlayerStatistic>();
	if (PlayerState != nullptr)
	{
		PlayerState->PlayerAlive.AddDynamic(this, &ABaseHUD::OnPlayerAlive);
		PlayerState->PlayerDead.AddDynamic(this, &ABaseHUD::OnPlayerDead);
	}
}

UGame_Interface* ABaseHUD::GetHUDWidget()
{
	return HUDWidget;
}

UStatisticsMenu* ABaseHUD::GetTabWidget()
{
	return TabWidget;
}

void ABaseHUD::OnPlayerAlive()
{
	ToggleHUD(true);
	ToggleSpectatorHUD(false);
}

void ABaseHUD::OnPlayerDead(ABaseTank* DeathInstigator)
{
	ToggleHUD(false);
	ToggleSpectatorHUD(true);
	if (SpectatorWidget != nullptr)
	{
		SpectatorWidget->SetDeathInfo(DeathInstigator);
	}
}
