// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStatisticTeam.h"
#include <MyGAME2/Enums/E_Team.h>
#include <Kismet/KismetMathLibrary.h>
#include <Kismet/GameplayStatics.h>
#include <algorithm>
#include <Algo/Count.h>
#include <Net/UnrealNetwork.h>
#include <MyGAME2/Game/TeamGameState.h>
#include <MyGAME2/Enums/E_Team.h>
#include "../BaseTank.h"
#include <GameFramework/Controller.h>



void APlayerStatisticTeam::BeginPlay()
{
	APlayerStatistic::BeginPlay();
	if (HasAuthority())
	{
		Team = GetRandomTeam();
		Team = GetBalansedSelectTeam(Team);
	}
	else if (GetOwningController() != nullptr)
	{
		Cast<ABaseGameState>(UGameplayStatics::GetGameState(this))->RoundStarted.AddDynamic(this, &APlayerStatisticTeam::OnStartRound);
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

E_Team APlayerStatisticTeam::GetBalansedSelectTeam(TEnumAsByte<enum E_Team> team)
{
	ATeamGameState* Game_State = Cast<ATeamGameState>(UGameplayStatics::GetGameState(this));
	if (Game_State != nullptr)
	{
		int valueTeam = Algo::CountIf<TArray<TObjectPtr<APlayerState>>>(Game_State->PlayerArray, [&team](APlayerState *value)
		{
			return Cast<APlayerStatisticTeam>(value)->Team == team;
		});

		if (valueTeam < (Game_State->PlayerArray.Num() / 2))
		{
			return team == E_Team::Team_A ? E_Team::Team_A : E_Team::Team_B;
		}
		else if (valueTeam > (Game_State->PlayerArray.Num() / 2))
		{
			return  team == E_Team::Team_A ? E_Team::Team_B : E_Team::Team_A;
		}
	}
	
	return team;
	
}

void APlayerStatisticTeam::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	APlayerStatistic::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APlayerStatisticTeam, Team);
}


void APlayerStatisticTeam::OnStartRound()
{
		TArray<AActor*, FDefaultAllocator> ArrPlayerStat;
		UGameplayStatics::GetAllActorsOfClass(this, APlayerStatisticTeam::StaticClass(), ArrPlayerStat);
		ArrPlayerStat.Remove(this);
		for (auto& el : ArrPlayerStat)
		{
			APlayerStatisticTeam* temaPlayerState = Cast<APlayerStatisticTeam>(el);
			if (Team == temaPlayerState->Team)
			{
				Cast<ABaseTank>(temaPlayerState->GetPawn())->ActivateOurTeamMaterial();
			}	
		}
}
