// Fill out your copyright notice in the Description page of Project Settings.


#include "W_TeamResultsEndRound.h"
#include <Kismet/GameplayStatics.h>
#include <MyGAME2/Game/TeamGameState.h>
#include <MyGAME2/Enums/E_Team.h>
#include <MyGAME2/Game/PlayerStatisticTeam.h>
#include <Kismet/KismetMathLibrary.h>
#include <Components/TextBlock.h>



void UW_TeamResultsEndRound::InitializeTextResult()
{
	ATeamGameState* p_teamGameState = Cast<ATeamGameState>(UGameplayStatics::GetGameState(this));

	bool isWinTeamA = p_teamGameState->GetPoints(E_Team::Team_A) > p_teamGameState->GetPoints(E_Team::Team_B);
	
	if (isWinTeamA && GetOwningPlayer()->GetPlayerState<APlayerStatisticTeam>()->Team == E_Team::Team_A)
	{
		T_Winner->SetText(FText::FromString("Victory"));
		FLinearColor color = FLinearColor(0.f, 0.f, 1.f, 1.f); // Blue color
		T_Winner->SetColorAndOpacity(FSlateColor(color));
	}
	else if (!isWinTeamA && GetOwningPlayer()->GetPlayerState<APlayerStatisticTeam>()->Team == E_Team::Team_B)
	{
		T_Winner->SetText(FText::FromString("Victory"));
		FLinearColor color = FLinearColor(0.f, 0.f, 1.f, 1.f); // Blue color
		T_Winner->SetColorAndOpacity(FSlateColor(color));
	}
	else
	{
		T_Winner->SetText(FText::FromString("Defeat"));
		FLinearColor color = FLinearColor(1.f, 0.f, 0.f, 1.f); // Red color
		T_Winner->SetColorAndOpacity(FSlateColor(color));
	}
}
