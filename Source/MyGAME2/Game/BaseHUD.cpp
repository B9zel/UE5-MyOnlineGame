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
#include "../Widgets/Ganeral/Chat/W_ChatInterface.h"
#include "../Widgets/InGame/W_SuperPower.h"
#include "../Widgets/InGame/W_Aim.h"
#include "../BaseTank.h"
#include "../PawnController.h"
#include "../Widgets/EndRound/W_EndRoundMapVote.h"
#include "../Widgets/Ganeral/PauseMenu/W_PauseMenu.h"
#include "../Widgets/InGame/Waiting/W_Waiting.h"
#include "../Widgets/InGame/W_TakeDamage.h"
#include "../Widget_Reload.h"


ABaseHUD::~ABaseHUD()
{
	m_HUDWidget = nullptr;
	m_TabWidget = nullptr;
	m_EndRoundWidget = nullptr;
	m_ChatWidget = nullptr;
	m_PreRoundWidget = nullptr;
	m_SpectatorWidget = nullptr;
	m_superskillWidget = nullptr;
	m_aimWidget = nullptr;

	isActivatePauseMenu = false;
}

void ABaseHUD::BeginPlay()
{
	Super::BeginPlay();

	CreateChat();
	
	ABaseGameState* pGameState = Cast<ABaseGameState>(UGameplayStatics::GetGameState(this));
	if (pGameState != nullptr)
	{
		pGameState->RoundStarted.AddDynamic(this, &ABaseHUD::OnRoundStarted);
		pGameState->RoundEnded.AddDynamic(this, &ABaseHUD::OnRoundEnded);

		switch (pGameState->RoundInProgress)
		{
		case E_GameState::PreStart:
			TogglePreRound(true);
			break;
		case E_GameState::Game:
			ToggleWaitingMenu(true);
			break;
		case E_GameState::EndGame:
			ToggleEndRound(true);
			break;
		default:
			break;
		}
	}
}

void ABaseHUD::ToggleHUD(bool isShow)
{
	if (isShow)
	{
		if (Cast<ABaseGameState>(UGameplayStatics::GetGameState(this))->RoundInProgress == E_GameState::Game)
		{
			if (Cast<APlayerStatistic>(GetOwningPlayerController()->GetPlayerState<APlayerStatistic>())->isAlive )
			{
				if (m_HUDWidget == nullptr)
				{
					m_HUDWidget = CreateWidget<UGame_Interface>(GetOwningPlayerController(), HUDWidgetClass);
				}
				if (!m_HUDWidget->IsInViewport())
					m_HUDWidget->AddToViewport();
			}
		}
	}
	else
	{
		if (m_HUDWidget != nullptr)
		{
			m_HUDWidget->RemoveFromParent();
		}
	}
}

void ABaseHUD::ToggleTab(bool isShow)
{
	if (isShow)//&& !isActivatePauseMenu
	{
		if (Cast<ABaseGameState>(UGameplayStatics::GetGameState(this))->RoundInProgress == E_GameState::Game)
		{
			if (m_TabWidget == nullptr)
			{
				m_TabWidget = CreateWidget<UStatisticsMenu>(GetOwningPlayerController(), TabWidgetClass);
			}
			if (!m_TabWidget->IsInViewport())
				m_TabWidget->AddToViewport();
		}
	}
	else
	{
		if (m_TabWidget != nullptr)
		{
			m_TabWidget->RemoveFromParent();
			//m_TabWidget = nullptr;
		}
	}
}

UW_Spectator* ABaseHUD::ToggleSpectatorHUD(bool isShow)
{
	if (isShow)
	{
		if (Cast<ABaseGameState>(UGameplayStatics::GetGameState(this))->RoundInProgress == E_GameState::Game)
		{
			if (m_SpectatorWidget == nullptr)
			{
				m_SpectatorWidget = CreateWidget<UW_Spectator>(GetOwningPlayerController(), SpectatorWidgetClass);
			}
			m_SpectatorWidget->AddToViewport();
		}
	}
	else
	{
		if (m_SpectatorWidget != nullptr)
		{
			m_SpectatorWidget->RemoveFromParent();
		}
	}
	return m_SpectatorWidget;
}

UW_PreRound* ABaseHUD::TogglePreRound(bool isShow)
{	
	if (isShow)
	{
		if (m_PreRoundWidget == nullptr)
		{
			m_PreRoundWidget = CreateWidget<UW_PreRound>(GetOwningPlayerController(), PreRoundWidgetClass);
		}
		m_PreRoundWidget->AddToViewport();

		GetOwner<APawnController>()->SetInputOnUI(true, m_PreRoundWidget);
	}
	else
	{
		if (m_PreRoundWidget != nullptr)
		{
			m_PreRoundWidget->RemoveFromParent();
		}
		
		if (!IsActivatePauseMenu())
		{
			GetOwner<APawnController>()->SetInputOnUI(false);
		}		
	}
	return m_PreRoundWidget;
}

UW_ResultsEndRound* ABaseHUD::ToggleEndRound(bool isShow)
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
		}
		GetOwner<APawnController>()->SetInputOnUI(false);
	}
	return m_EndRoundWidget;
}

void ABaseHUD::ToggleChat(bool isActivate)
{
	if (!isActivatePauseMenu)
	{
		if (isActivate)
		{
			m_ChatWidget->Activate();
		}
		else
		{
			m_ChatWidget->Deactivate();
			switch (Cast<ABaseGameState>(UGameplayStatics::GetGameState(this))->RoundInProgress)
			{
			case E_GameState::PreStart:
				GetOwner<APawnController>()->SetInputOnUI(true,m_PreRoundWidget);
				break;
			case E_GameState::Game:
				GetOwner<APawnController>()->SetInputOnUI(false);
				break;
			case E_GameState::EndGame:
				GetOwner<APawnController>()->SetInputOnUI(true, m_EndRoundWidget);
				break;
			default:
				break;
			}
		}
	}
}

UW_SuperPower* ABaseHUD::ToggleSuperPower(bool isShow, bool isRemove)
{
	if (isShow)
	{
		if (Cast<ABaseGameState>(UGameplayStatics::GetGameState(this))->RoundInProgress == E_GameState::Game)
		{
			if (m_superskillWidget == nullptr)
			{
				m_superskillWidget = CreateWidget<UW_SuperPower>(GetOwningPlayerController(), superskillWidgetClass);
				m_superskillWidget->AddToViewport();
			}
			else
			{
				m_superskillWidget->SetVisibility(ESlateVisibility::Visible);
			}
		}
	}
	else
	{
		if (isRemove && m_superskillWidget != nullptr)
		{
			m_superskillWidget->RemoveFromParent();
		}
		else if (m_superskillWidget != nullptr)
		{
			m_superskillWidget->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
	return m_superskillWidget;
}

UW_Aim* ABaseHUD::ToggleAim(bool isShow)
{
	if (isShow)
	{
		if (m_aimWidget == nullptr)
		{
			m_aimWidget = CreateWidget<UW_Aim>(GetOwningPlayerController(), AimWidgetClass);
		}
		if (!m_aimWidget->IsInViewport())
			m_aimWidget->AddToViewport(-1);
	}
	else if (m_aimWidget != nullptr)
	{
		if (m_aimWidget->IsInViewport())
			m_aimWidget->RemoveFromParent();
	}
	return m_aimWidget;
}

UW_PauseMenu* ABaseHUD::TogglePauseMenu(bool isShow)
{
	if (isShow)
	{
		if (m_PauseMenuWidget == nullptr)
		{
			m_PauseMenuWidget = CreateWidget<UW_PauseMenu>(GetOwningPlayerController(), PauseMenuWidgetClass);
		}
		m_PauseMenuWidget->AddToViewport(2);

		GetOwner<APawnController>()->SetInputOnUI(true, m_PauseMenuWidget);
		isActivatePauseMenu = true;
	}
	else 
	{
		if (m_PauseMenuWidget != nullptr)
		{
			m_PauseMenuWidget->RemoveFromParent();

			isActivatePauseMenu = false;
		}
		switch (Cast<ABaseGameState>(UGameplayStatics::GetGameState(this))->RoundInProgress)
		{
		case E_GameState::PreStart:
			GetOwner<APawnController>()->SetInputOnUI(true,m_PreRoundWidget);
			break;
		case E_GameState::Game:
			GetOwner<APawnController>()->SetInputOnUI(false);
			break;
		case E_GameState::EndGame:
			GetOwner<APawnController>()->SetInputOnUI(true, m_EndRoundWidget);
			break;
		}
	}
	return m_PauseMenuWidget;
}

UW_Waiting* ABaseHUD::ToggleWaitingMenu(bool isShow)
{
	if (isShow)
	{
		if (m_WaitingWidget == nullptr)
		{
			m_WaitingWidget = CreateWidget<UW_Waiting>(GetOwningPlayerController(), WaitingWidgetClass);
		}
		m_WaitingWidget->AddToViewport();
	}
	else
	{
		if (m_WaitingWidget != nullptr)
		{
			m_WaitingWidget->RemoveFromParent();
			m_WaitingWidget = nullptr;
		}
	}
	return m_WaitingWidget;
}

UW_TakeDamage* ABaseHUD::ToggleTakeDamage(bool isShow, float Damage, const FVector& WorldPosition)
{
	if (isShow)
	{
		if (Cast<ABaseGameState>(UGameplayStatics::GetGameState(this))->RoundInProgress == E_GameState::Game)
		{
			if (m_TakeDamageWidget == nullptr)
			{
				m_TakeDamageWidget = CreateWidget<UW_TakeDamage>(GetOwningPlayerController(), TakeDamageWidgetClass);
				m_TakeDamageWidget->Damage = Damage;
				m_TakeDamageWidget->WorldLocation = WorldPosition;
			}
			m_TakeDamageWidget->AddToViewport();
		}
	}
	else
	{
		if (m_TakeDamageWidget != nullptr)
		{
			m_TakeDamageWidget->RemoveFromParent();
			m_TakeDamageWidget = nullptr;
		}
	}
	
	return m_TakeDamageWidget;
}


void ABaseHUD::ActivateReload(float Time, float Rate, float Step)
{
	if (m_HUDWidget != nullptr)
	{
		m_HUDWidget->ReloadStats->Construct_Widget(Time, Rate, Step);
	}
}

void ABaseHUD::DeactivateReload()
{
	if (m_HUDWidget != nullptr)
	{
		m_HUDWidget->ReloadStats->DestructWidget();
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
		//PlayerState->GetPlayerController()->GetPawn<ABaseTank>()->D_SpawnTankPawn.AddDynamic(this, &ABaseHUD::OnSpawnTankPawn);
	}
}

void ABaseHUD::OnRoundEnded()
{
	ToggleHUD(false);
	ToggleTab(false);
	ToggleAim(false);
	ToggleSuperPower(false, true);
	ToggleWaitingMenu(false);
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

const UW_ChatInterface* ABaseHUD::GetChatWidget() const
{
	return m_ChatWidget;
}

void ABaseHUD::OnPlayerAlive()
{
	ABaseTank* OwningPawn = Cast<ABaseTank>(GetOwningPawn());
	if (OwningPawn != nullptr)
	{
		OwningPawn->D_ReloadStart.AddDynamic(this, &ABaseHUD::StartReload);
		OwningPawn->D_ReloadEnd.AddDynamic(this, &ABaseHUD::FinishReload);
	}
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

UW_ChatInterface* ABaseHUD::CreateChat()
{
	//SubclassOf<UW_Chat> Chat = Cast<UW_Chat>(ChatWidgetClass.Get())->StaticClass();
	m_ChatWidget = CreateWidget<UW_ChatInterface>(GetOwningPlayerController(), ChatWidgetClass);
	m_ChatWidget->AddToViewport(-1);

	return m_ChatWidget;
}

bool ABaseHUD::isActivateChat()
{
	return m_ChatWidget->IsChatActivate();
}

bool ABaseHUD::IsActivatePauseMenu()
{
	return isActivatePauseMenu;
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

void ABaseHUD::StartReload(float Time, float Rate, float Step)
{
	ActivateReload(Time, Rate, Step);
}

void ABaseHUD::FinishReload()
{
	DeactivateReload();
}
