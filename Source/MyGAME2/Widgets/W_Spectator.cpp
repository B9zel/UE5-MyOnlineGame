// Fill out your copyright notice in the Description page of Project Settings.


#include "W_Spectator.h"
#include <MyGAME2/Widgets/W_RoundTime.h>
#include <MyGAME2/BaseTank.h>
#include <MyGAME2/Widgets/W_SpectateInfoKill.h>
#include <MyGAME2/Game/PlayerStatistic.h>


void UW_Spectator::SetDeathInfo(ABaseTank* Instigator)
{
	InfoKill->SetKilledInfo(Cast<APlayerStatistic>(Instigator->GetPlayerState()));
}
