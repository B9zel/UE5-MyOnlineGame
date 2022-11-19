// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStatisticTeam.h"
#include <MyGAME2/Enums/E_Team.h>
#include <Kismet/KismetMathLibrary.h>
#include <Net/UnrealNetwork.h>


void APlayerStatisticTeam::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority())
	{	
		Team = GetRandomTeam();
	}
}

E_Team APlayerStatisticTeam::GetRandomTeam()
{
	switch (UKismetMathLibrary::RandomInteger(E_Team::TotalTeam))
	{
	case 0:
		return E_Team::Team_A;
	case 1:
		return E_Team::Team_B;
	default:
		return E_Team();
	}
}

void APlayerStatisticTeam::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	APlayerStatistic::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APlayerStatisticTeam, Team);
}
