// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStatistic.h"
#include <MyGAME2/BaseTank.h>
#include <Net/UnrealNetwork.h>
#include <MyGAME2/Widgets/PlayerStat.h>
#include <MyGAME2/Game/BaseHUD.h>
#include <MyGAME2/Widgets/StatisticsMenu.h>


APlayerStatistic::APlayerStatistic()
{
	SetReplicates(true);

	Kills = 0;

	Deaths = 0;
	
	isAlive = false;
}

void APlayerStatistic::BeginPlay()
{
	Super::BeginPlay();

	
}
void APlayerStatistic::SwitchWidgetNames()
{
	if (isAlive)
	{
		PlayerAlive.Broadcast();
	}
}

void APlayerStatistic::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APlayerStatistic, Kills);

	DOREPLIFETIME(APlayerStatistic, Deaths);

	DOREPLIFETIME(APlayerStatistic, isAlive);
}



void APlayerStatistic::AddKill()
{
	++Kills;
}

void APlayerStatistic::AddDeath()
{
	++Deaths;
}

void APlayerStatistic::OnwerPawnDead_Implementation(ABaseTank* DeadInstigator)
{
	isAlive = false;
	PlayerDead.Broadcast(DeadInstigator);
}

