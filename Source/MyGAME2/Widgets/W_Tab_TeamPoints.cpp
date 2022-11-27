// Fill out your copyright notice in the Description page of Project Settings.


#include "W_Tab_TeamPoints.h"
#include <Components/TextBlock.h>
#include <MyGAME2/Game/TeamGameState.h>
#include <Kismet/GameplayStatics.h>
#include <MyGAME2/Enums/E_Team.h>
#include <MyGAME2/Game/PlayerStatisticTeam.h>
#include <Styling/SlateColor.h>


void UW_Tab_TeamPoints::NativeConstruct()
{
	TextPoints->TextDelegate.BindDynamic(this, &UW_Tab_TeamPoints::BindTextPoints);
	//TextPoints->ColorAndOpacityDelegate.BindDynamic(this, &UW_Tab_TeamPoints::BindColor);
	TextPoints->SynchronizeProperties();

	Team = GetOwningPlayerState<APlayerStatisticTeam>()->Team;
	Game_State = Cast<ATeamGameState>(UGameplayStatics::GetGameState(this));
}

FText UW_Tab_TeamPoints::BindTextPoints()
{
	if (isOwnTeam)
	{
		return FText::FromString(FString::FromInt(Game_State->GetPoints(this->Team)));
	}
	else
	{
		switch (Team)
		{
		case E_Team::Team_A:
			return FText::FromString(FString::FromInt(Game_State->GetPoints(E_Team::Team_B)));
		case E_Team::Team_B:
			return FText::FromString(FString::FromInt(Game_State->GetPoints(E_Team::Team_A)));
		default:
			return FText();
			break;
		}
	}
	
}

//FSlateColor UW_Tab_TeamPoints::BindColor()
//{
//	if (this->Team == GetOwningPlayerState<APlayerStatisticTeam>()->Team)
//	{
//		return OurTeamColor;
//	}
//	else
//	{
//		return OppositeTeamColor;
//	}
//}
