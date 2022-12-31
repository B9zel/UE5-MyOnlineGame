// Fill out your copyright notice in the Description page of Project Settings.
#include "BaseHUD.h"
#include <MyGAME2/Widgets/StatisticsMenu.h>
#include <MyGAME2/Game_Interface.h>
#include <MyGAME2/Game/BaseGameState.h>
#include <Kismet/GameplayStatics.h>
#include <MyGAME2/Game/PlayerStatistic.h>
#include <MyGAME2/Widgets/W_Spectator.h>
#include "../Enums/E_GameState.h"
#include "../Widgets/PreRound/W_PreRound.h"
#include "../Widgets/EndRound/W_ResultsEndRound.h"


ABaseHUD::~ABaseHUD()
{
	m_HUDWidget = nullptr;
	m_TabWidget = nullptr;
}

void ABaseHUD::BeginPlay()
{
	Super::BeginPlay();

	TogglePreRound(true);
	ABaseGameState* pGameState = Cast<ABaseGameState>(UGameplayStatics::GetGameState(this));
	pGameState->RoundStarted.AddDynamic(this, &ABaseHUD::OnRoundStarted);
	pGameState->RoundEnded.AddDynamic(this, &ABaseHUD::OnRoundEnded);
}

void ABaseHUD::ToggleHUD(bool isShow)
{
	if (isShow)
	{
		if (Cast<APlayerStatistic>(GetOwningPlayerController()->GetPlayerState<APlayerStatistic>())->isAlive)
		{
			if (m_HUDWidget == nullptr)
			{
				m_HUDWidget = CreateWidget<UGame_Interface>(GetOwningPlayerController(), HUDWidgetClass);
			}
			m_HUDWidget->AddToViewport();
		}
	}
	else
	{
		if (m_HUDWidget != nullptr)
		{
			m_HUDWidget->RemoveFromParent();
			m_HUDWidget = nullptr;
		}
	}
}

void ABaseHUD::ToggleTab(bool isShow)
{
	if (Cast<ABaseGameState>(UGameplayStatics::GetGameState(this))->RoundInProgress == E_GameState::Game)
	{
		if (isShow)
		{
			if (m_TabWidget == nullptr)
			{
				m_TabWidget = CreateWidget<UStatisticsMenu>(GetOwningPlayerController(), TabWidgetClass);
			}
			m_TabWidget->AddToViewport();
		}
		else
		{
			if (m_TabWidget != nullptr)
			{
				m_TabWidget->RemoveFromParent();
				m_TabWidget = nullptr;
			}
		}
	}
}

void ABaseHUD::ToggleSpectatorHUD(bool isShow)
{
	if (Cast<ABaseGameState>(UGameplayStatics::GetGameState(this))->RoundInProgress == E_GameState::Game)
	{
		if (isShow)
		{
			if (m_SpectatorWidget == nullptr)
			{
				m_SpectatorWidget = CreateWidget<UW_Spectator>(GetOwningPlayerController(), SpectatorWidgetClass);
			}
			m_SpectatorWidget->AddToViewport();
		}
		else
		{
			if (m_SpectatorWidget != nullptr)
			{
				m_SpectatorWidget->RemoveFromParent();
				m_SpectatorWidget = nullptr;
			}
		}
	}
}

void ABaseHUD::TogglePreRound(bool isShow)
{
	if (isShow)
	{
		if (m_PreRoundWidget == nullptr)
		{
			m_PreRoundWidget = CreateWidget<UW_PreRound>(GetOwningPlayerController(), PreRoundWidgetClass);
		}
		m_PreRoundWidget->AddToViewport();
	}
	else
	{
		if (m_PreRoundWidget != nullptr)
		{
			m_PreRoundWidget->RemoveFromParent();
			m_PreRoundWidget = nullptr;
		}
	}
}

void ABaseHUD::ToggleEndRound(bool isShow)
{
	if (isShow)
	{
		if (m_EndRoundWidget == nullptr)
		{
			m_EndRoundWidget = CreateWidget<UW_ResultsEndRound>(GetOwningPlayerController(), EndRoundWidgetClass);
		}
		m_EndRoundWidget->AddToViewport();
	}
	else
	{
		if (m_EndRoundWidget != nullptr)
		{
			m_EndRoundWidget->RemoveFromParent();
			m_EndRoundWidget = nullptr;
		}
	}
}

void ABaseHUD::OnRoundStarted()
{
	APlayerStatistic* PlayerState = GetOwningPlayerController()->GetPlayerState<APlayerStatistic>();
	TogglePreRound(false);
	ToggleHUD(true);
	if (PlayerState != nullptr)
	{
		PlayerState->PlayerAlive.AddDynamic(this, &ABaseHUD::OnPlayerAlive);
		PlayerState->PlayerDead.AddDynamic(this, &ABaseHUD::OnPlayerDead);
	}
}

void ABaseHUD::OnRoundEnded()
{
	ToggleHUD(false);
	ToggleTab(false);
	ToggleSpectatorHUD(false);
	ToggleEndRound(true);
}

UGame_Interface* ABaseHUD::GetHUDWidget()
{
	return m_HUDWidget;
}

UStatisticsMenu* ABaseHUD::GetTabWidget()
{
	return m_TabWidget;
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
	if (m_SpectatorWidget != nullptr && Cast<ABaseGameState>(UGameplayStatics::GetGameState(this))->RoundInProgress == E_GameState::Game)
	{
		m_SpectatorWidget->SetDeathInfo(DeathInstigator);
	}
}
