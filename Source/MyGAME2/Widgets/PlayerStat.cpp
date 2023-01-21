// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStat.h"
#include <Components/TextBlock.h>
#include <MyGAME2/Game/PlayerStatistic.h>
#include <Styling/SlateColor.h>
#include <Components/Border.h>


void UPlayerStat::NativeConstruct()
{
	Super::NativeConstruct();

	NickName->TextDelegate.BindDynamic(this, &UPlayerStat::BindNickName);
	NickName->ColorAndOpacityDelegate.BindDynamic(this, &UPlayerStat::BindColorName);
	NickName->SynchronizeProperties();

	Deaths->TextDelegate.BindDynamic(this, &UPlayerStat::BindDeaths);
	Deaths->SynchronizeProperties();
	
	Kills->TextDelegate.BindDynamic(this, &UPlayerStat::BindKills);
	Kills->SynchronizeProperties();

	if (PlayerState->GetPlayerController() == GetOwningPlayer())
	{
		NickName->SetColorAndOpacity(colorAllComponents);
		Deaths->SetColorAndOpacity(colorAllComponents);
		Kills->SetColorAndOpacity(colorAllComponents);
	}
}



FText UPlayerStat::BindNickName()
{
	return FText::FromString(PlayerState->GetPlayerName());
}

FSlateColor UPlayerStat::BindColorName()
{
	FLinearColor Color(1,1,1);
	if (!PlayerState->isAlive)
	{
		Color = FLinearColor(0.1f, 0.0f, 0.0f, 0.65f);
	}
	else if (PlayerState->GetPlayerController() == GetOwningPlayer())
	{
		Color = FLinearColor(0.f, 1.f, 1.f, 1.f);
	}
	return FSlateColor(Color);
}

FText UPlayerStat::BindDeaths()
{
	return FText::FromString(FString::FromInt(PlayerState->Deaths));
}

FText UPlayerStat::BindKills()
{
	return FText::FromString(FString::FromInt(PlayerState->Kills));
}
