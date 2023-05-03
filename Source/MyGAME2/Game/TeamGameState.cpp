// Fill out your copyright notice in the Description page of Project Settings.


#include "TeamGameState.h"
#include <MyGAME2/Enums/E_Team.h>
#include <Containers/Map.h>
#include <MyGAME2/Game/PlayerStatisticTeam.h>
#include <Net/UnrealNetwork.h>
#include "../Enums/E_GameState.h"
#include <Kismet/GameplayStatics.h>
#include "Base_GameMode.h"




ATeamGameState::ATeamGameState()
{
	TeamPoints.Emplace(E_Team::Team_A, 0);
	TeamPoints.Emplace(E_Team::Team_B, 0);

	PointsArray.SetNum(TeamPoints.Num());
	
}


int ATeamGameState::GetPoints(E_Team Team)
{
	return PointsArray[Team];
}

void ATeamGameState::ChangetTeamPoints(E_Team Team, int Value)
{
	TeamPoints.Add(Team, *TeamPoints.Find(Team) + Value);
	PointsArray[Team] = *TeamPoints.Find(Team);
}

void ATeamGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	ABaseGameState::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATeamGameState, PointsArray);
	
}

void ATeamGameState::TickPreRoundTime()
{
	if (PlayerArray.Num() >= playerInSession)
	{
		PreStartRoundTimer -= FTimespan::FromSeconds(1.0f);
		if (PreStartRoundTimer.GetTotalSeconds() <= 0 && RoundInProgress == E_GameState::PreStart)
		{
			/*if (HasAuthority())
			{
				for (auto& el : PlayerArray)
				{
					APlayerStatisticTeam* l_PlayerState = Cast<APlayerStatisticTeam>(el);

					l_PlayerState->Team = l_PlayerState->GetBalansedSelectTeam(l_PlayerState->Team);
				}
			}*/

			Cast<ABase_GameMode>(UGameplayStatics::GetGameMode(this))->StartRound();
			RoundInProgress = E_GameState::Game;
			RoundStarted.Broadcast();
		}
	}
	else
	{
		PreStartRoundTimer = FTimespan::FromSeconds(10);
	}
}
