// Fill out your copyright notice in the Description page of Project Settings.


#include "W_TeamStatisticsMenu.h"
#include <Components/VerticalBox.h>
#include <MyGAME2/Game/PlayerStatisticTeam.h>
#include <MyGAME2/Enums/E_Team.h>



UVerticalBox* UW_TeamStatisticsMenu::GetPlayerList(APlayerState* PlayerState)
{
	if (Cast<APlayerStatisticTeam>(PlayerState)->Team == GetOwningPlayerState<APlayerStatisticTeam>()->Team) // E_Team::Team_A
	{
		return VB_PlayerOwn;
	}
	else
	{
		return VB_Player;
	}
}

void UW_TeamStatisticsMenu::UpdatePlayerList()
{
	VB_PlayerOwn->ClearChildren();
	UStatisticsMenu::UpdatePlayerList();
}