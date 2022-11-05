// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStatistic.h"
#include <MyGAME2/BaseTank.h>
#include <Net/UnrealNetwork.h>

APlayerStatistic::APlayerStatistic()
{
	SetReplicates(true);

	Kills = 0;

	Deaths = 0;
}

void APlayerStatistic::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APlayerStatistic, Kills);

	DOREPLIFETIME(APlayerStatistic, Deaths);
}

void APlayerStatistic::AddKill()
{
	++Kills;
}

void APlayerStatistic::AddDeath()
{
	++Deaths;
}

