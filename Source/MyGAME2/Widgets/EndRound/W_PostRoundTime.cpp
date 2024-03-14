// Fill out your copyright notice in the Description page of Project Settings.


#include "W_PostRoundTime.h"
#include <Components/TextBlock.h>
#include "../../Game/Components/VoteComponent.h"
#include "../../Game/BaseGameState.h"



void UW_PostRoundTime::NativeConstruct()
{
	UW_RoundTime::NativeConstruct();

	T_NextMap->TextDelegate.BindDynamic(this, &UW_PostRoundTime::UpdateNextMap);
	T_NextMap->SynchronizeProperties();
}

FText UW_PostRoundTime::UpdateTimerTick()
{
	if (Game_State->voteComponent->voteMapTime < 10)
	{
		return FText::FromString("00:0" + FString::FromInt(Game_State->voteComponent->voteMapTime));
	}
	else
	{
		return FText::FromString("00:" + FString::FromInt(Game_State->voteComponent->voteMapTime));
	}
}

FText UW_PostRoundTime::UpdateNextMap()
{
	if (Game_State != nullptr)
	{
		return FText::FromString(TextNextMap.ToString() + Game_State->voteComponent->GetShowNameMapWithMaxVote());
	}
	else
	{
		return FText::FromString(TextNextMap.ToString() + FString(""));

	}
}
