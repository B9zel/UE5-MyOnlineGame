// Fill out your copyright notice in the Description page of Project Settings.


#include "StatisticsMenu.h"
#include <Components/TextBlock.h>
#include <Components/VerticalBox.h>
#include <MyGAME2/Game/BaseGameState.h>
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetStringLibrary.h>
#include <Kismet/GameplayStatics.h>
#include "PlayerStat.h"
#include <MyGAME2/Game/BaseGameState.h>
#include <MyGAME2/Game/PlayerStatistic.h>



void UStatisticsMenu::NativeConstruct()
{
	Super::NativeConstruct();

	Timer->TextDelegate.BindDynamic(this, &UStatisticsMenu::UpdateTimerTick);
	Timer->SynchronizeProperties();
	Game_State = GetBaseGameState();

	UpdatePlayerList();
}

ABaseGameState* UStatisticsMenu::GetBaseGameState()
{
	return Cast<ABaseGameState>(UGameplayStatics::GetGameState(this));
}

void UStatisticsMenu::UpdatePlayerList()
{
	VB_PlayerState->ClearChildren();
	for (auto& el : Game_State->PlayerArray)
	{
		UPlayerStat* widget = CreateWidget<UPlayerStat>(GetOwningPlayer(), UserWidget);
		widget->PlayerState = Cast<APlayerStatistic>(el);
		VB_PlayerState->AddChildToVerticalBox(widget);
	}
}

FText UStatisticsMenu::UpdateTimerTick()
{
	if (Game_State == nullptr)
	{
		Game_State = GetBaseGameState();
	}
	return FText::AsTimespan(Game_State->RoundTime);
}
												
