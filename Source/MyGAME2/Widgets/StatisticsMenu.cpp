// Fill out your copyright notice in the Description page of Project Settings.


#include "StatisticsMenu.h"
#include <Components/TextBlock.h>
#include <Components/VerticalBox.h>
#include <Kismet/GameplayStatics.h>
#include "PlayerStat.h"
#include <MyGAME2/Game/BaseGameState.h>
#include <MyGAME2/Game/PlayerStatistic.h>
#include <MyGAME2/Widgets/W_RoundTime.h>



void UStatisticsMenu::NativeConstruct()
{
	Super::NativeConstruct();

	Game_State = GetBaseGameState();
	UpdatePlayerList();
}

ABaseGameState* UStatisticsMenu::GetBaseGameState()
{
	return Cast<ABaseGameState>(UGameplayStatics::GetGameState(this));
}

UVerticalBox* UStatisticsMenu::GetPlayerList(APlayerState* PlayerStat)
{
	return VB_Player;
}

void UStatisticsMenu::UpdatePlayerList()
{
	for (auto& el : Game_State->PlayerArray)
	{
		UPlayerStat* widget = CreateWidget<UPlayerStat>(GetOwningPlayer(), UserWidget);
		widget->PlayerState = Cast<APlayerStatistic>(el);
		GetPlayerList(el)->AddChildToVerticalBox(widget);
	}
}
