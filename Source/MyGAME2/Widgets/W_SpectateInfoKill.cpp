// Fill out your copyright notice in the Description page of Project Settings.


#include <MyGAME2/Widgets/W_SpectateInfoKill.h>
#include <Components/TextBlock.h>
#include <MyGAME2/BaseTank.h>
#include <MyGAME2/Game/PlayerStatistic.h>



void UW_SpectateInfoKill::SetKilledInfo(APlayerStatistic* PlayerState)
{
	if (PlayerState != nullptr)
	{
		NameKiller->SetText(FText::FromString(PlayerState->GetPlayerName()));
	}
}
