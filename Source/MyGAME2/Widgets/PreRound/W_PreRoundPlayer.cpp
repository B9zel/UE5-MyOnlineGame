// Fill out your copyright notice in the Description page of Project Settings.
#include "W_PreRoundPlayer.h"
#include <Components/TextBlock.h>
#include <MyGAME2/Game/PlayerStatistic.h>
#include <MyGAME2/Game/PlayerStatistic.h>


void UW_PreRoundPlayer::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerName->TextDelegate.BindDynamic(this, &UW_PreRoundPlayer::BindPlayerName);
	PlayerName->SynchronizeProperties();
}


FText UW_PreRoundPlayer::BindPlayerName()
{
	return FText::FromString(PlayerState->GetPlayerName());
}
