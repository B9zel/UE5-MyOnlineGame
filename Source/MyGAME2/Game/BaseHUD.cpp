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
#include "../Widgets/Ganeral/Chat/W_Chat.h"
#include "../Widgets/InGame/W_SuperPower.h"
#include "../Widgets/InGame/W_Aim.h"
#include "../BaseTank.h"
#include "../PawnController.h"
#include "../Widgets/EndRound/W_EndRoundMapVote.h"



ABaseHUD::~ABaseHUD()
{
	m_HUDWidget = nullptr;
	m_TabWidget = nullptr;
	m_EndRoundWidget = nullptr;
	m_ChatWidget = nullptr;
	m_PreRoundWidget = nullptr;
	m_SpectatorWidget = nullptr;
}

void ABaseHUD::BeginPlay()
{
	Super::BeginPlay();

	TogglePreRound(true);
	CreateChat();
	ABaseGameState* pGameState = Cast<ABaseGameState>(UGameplayStatics::GetGameState(this));
	if (pGameState != nullptr)
	{
		pGameState->RoundStarted.AddDynamic(this, &ABaseHUD::OnRoundStarted);
		pGameState->RoundEnded.AddDynamic(this, &ABaseHUD::OnRoundEnded);
	}
	
}

void ABaseHUD::ToggleHUD(bool isShow)
{
	if (isShow)
	{
		if (Cast<ABaseGameState>(UGameplayStatics::GetGameState(this))->RoundInProgress == E_GameState::Game)
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
		GetOwner<APawnController>()->SetInputOnUI(true, m_EndRoundWidget->EndRoundMap);
	}
	else
	{
		if (m_EndRoundWidget != nullptr)
		{
			m_EndRoundWidget->RemoveFromParent();
			m_EndRoundWidget = nullptr;
		}
		GetOwner<APawnController>()->SetInputOnUI(false);
	}
}

void ABaseHUD::ToggleChat(bool isActivate)
{
	if (isActivate)
	{
		m_ChatWidget->ActivateChat();
	}
	else
	{
		m_ChatWidget->DeactivateChat();

		FInputModeGameOnly inputMode;
		GetOwningPlayerController()->SetInputMode(inputMode);
	}
}

void ABaseHUD::ToggleSuperPower(bool isShow, bool isRemove)
{
	if (Cast<ABaseGameState>(UGameplayStatics::GetGameState(this))->RoundInProgress != E_GameState::Game)
		return;

	if (isShow)
	{
		if (m_superskillWidget == nullptr)
		{
			m_superskillWidget = CreateWidget<UW_SuperPower>(GetOwningPlayerController(), superskillWidgetClass);
			m_superskillWidget->AddToViewport();
		}
		else if (m_superskillWidget != nullptr)
		{
			m_superskillWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}
	else
	{
		if (isRemove && m_superskillWidget != nullptr)
		{
			m_superskillWidget->RemoveFromParent();
			m_superskillWidget = nullptr;
		}
		else if (m_superskillWidget != nullptr)
		{
			m_superskillWidget->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void ABaseHUD::ToggleAim(bool isShow)
{
	if (isShow)
	{
		if (m_aimWidget == nullptr)
		{
			m_aimWidget = CreateWidget<UW_Aim>(GetOwningPlayerController(), AimWidgetClass);
		}
		m_aimWidget->AddToViewport(-1);
	}
	else if (m_aimWidget != nullptr)
	{
		m_aimWidget->RemoveFromParent();
		m_aimWidget = nullptr;
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
		PlayerState->GetPlayerController()->GetPawn<ABaseTank>()->D_SpawnTankPawn.AddDynamic(this, &ABaseHUD::OnSpawnTankPawn);
	}
	
	
}

void ABaseHUD::OnRoundEnded()
{
	ToggleHUD(false);
	ToggleTab(false);
	ToggleAim(false);
	ToggleSuperPower(false, true);
	ToggleSpectatorHUD(false);
	ToggleEndRound(true);
}

const UGame_Interface* ABaseHUD::GetHUDWidget() const
{
	return m_HUDWidget;
}

const UStatisticsMenu* ABaseHUD::GetTabWidget() const
{
	return m_TabWidget;
}

const UW_Chat* ABaseHUD::GetChatWidget() const
{
	return m_ChatWidget;
}

void ABaseHUD::OnPlayerAlive()
{
	ToggleSpectatorHUD(false);
	ToggleHUD(true);
	ToggleSuperPower(true);
}

void ABaseHUD::OnPlayerDead(ABaseTank* DeathInstigator)
{
	ToggleHUD(false);
	ToggleAim(false);
	ToggleSuperPower(false, true);
	ToggleSpectatorHUD(true);
	if (m_SpectatorWidget != nullptr && Cast<ABaseGameState>(UGameplayStatics::GetGameState(this))->RoundInProgress == E_GameState::Game)
	{
		m_SpectatorWidget->SetDeathInfo(DeathInstigator);
	}
}

void ABaseHUD::SetWidgetSuperPower(class UW_SuperPower* Widget)
{
	m_superskillWidget = Widget;
}

void ABaseHUD::CreateChat()
{
	m_ChatWidget = CreateWidget<UW_Chat>(GetOwningPlayerController(), ChatWidgetClass);
	m_ChatWidget->AddToViewport(0);
}

bool ABaseHUD::isActivateChat()
{
	return m_ChatWidget->isActivate;
}

void ABaseHUD::OnSpawnTankPawn(TSubclassOf<UW_SuperPower> Widget)
{
	superskillWidgetClass = Widget;
}


void ABaseHUD::ActivateSuperSkillWidget(float InRate)
{
	if (m_superskillWidget != nullptr)
	{
		m_superskillWidget->Activate(InRate);
	}
}

void ABaseHUD::ReloadSuperSkillWidget(float InRate)
{
	if (m_superskillWidget != nullptr)
	{
		m_superskillWidget->Reload(InRate);
	}
}
