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
	}
	else
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
			return team == E_Team::Team_A ? E_Team::Team_A : E_Team::Team_B;//Cast<APlayerStatisticTeam>(Game_State->PlayerArray[i])->Team = E_Team::Team_A;
		}
		else if (valueTeam > (Game_State->PlayerArray.Num() / 2))
		{
			return  team == E_Team::Team_A ? E_Team::Team_B : E_Team::Team_A;//Cast<APlayerStatisticTeam>(Game_State->PlayerArray[i])->Team = E_Team::Team_B;
		}
	}
	
	return team;
	/*for (int i = 0; i < Game_State->PlayerArray.Num(); i++)
	{
		if (valueTeamA < Game_State->PlayerArray.Num() / 2)
		{
		}
		else if (valueTeamA > Game_State->PlayerArray.Num() / 2)
		{
		}
	}*/
}

void APlayerStatisticTeam::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	APlayerStatistic::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APlayerStatisticTeam, Team);
}


void APlayerStatisticTeam::OnStartRound()
{
	if (GetOwningController() != nullptr)
	{
		TArray<AActor*, FDefaultAllocator> ArrPlayerStat;
		UGameplayStatics::GetAllActorsOfClass(this, APlayerState::StaticClass(), ArrPlayerStat);
		
		for (auto& el : ArrPlayerStat)
		{
			if (el != this)
			{
				APlayerStatisticTeam* temaPlayerState = Cast<APlayerStatisticTeam>(el);
				if (Team == temaPlayerState->Team)
				{
					Cast<ABaseTank>(temaPlayerState->GetPawn())->ActivateOurTeamMaterial();
				}	
			}
		}
	}
}
