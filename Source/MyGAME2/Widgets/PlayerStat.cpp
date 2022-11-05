// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStat.h"
#include <Components/TextBlock.h>
#include <MyGAME2/Game/PlayerStatistic.h>

void UPlayerStat::NativeConstruct()
{
	Super::NativeConstruct();

	NickName->TextDelegate.BindDynamic(this, &UPlayerStat::BindNickName);
	NickName->SynchronizeProperties();

	Deaths->TextDelegate.BindDynamic(this, &UPlayerStat::BindDeaths);
	Deaths->SynchronizeProperties();

	Kills->TextDelegate.BindDynamic(this, &UPlayerStat::BindKills);
	Kills->SynchronizeProperties();
}

FText UPlayerStat::BindNickName()
{
	return FText::FromString(PlayerState->GetPlayerName());
}

FText UPlayerStat::BindDeaths()
{
	return FText::FromString(FString::FromInt(PlayerState->Deaths));
}

FText UPlayerStat::BindKills()
{
	return FText::FromString(FString::FromInt(PlayerState->Kills));
}
