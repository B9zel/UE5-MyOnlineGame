// Fill out your copyright notice in the Description page of Project Settings.


#include "TeamGameState.h"
#include <MyGAME2/Enums/E_Team.h>
#include <Containers/Map.h>
#include <MyGAME2/Game/PlayerStatisticTeam.h>
#include <Net/UnrealNetwork.h>




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
