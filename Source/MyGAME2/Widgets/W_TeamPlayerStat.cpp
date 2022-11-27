// Fill out your copyright notice in the Description page of Project Settings.


#include "W_TeamPlayerStat.h"
#include <MyGAME2/Game/PlayerStatisticTeam.h>
#include <MyGAME2/Enums/E_Team.h>
#include <Styling/SlateColor.h>
#include <Components/Border.h>


void UW_TeamPlayerStat::NativeConstruct()
{
	UPlayerStat::NativeConstruct();

	SetColorTeam(OurTeamColor, OppositeTeamColor);

}

void UW_TeamPlayerStat::SetColorTeam(FSlateColor OurTeam, FSlateColor OppositeTeam)
{
	APlayerStatisticTeam* Player_State = Cast<APlayerStatisticTeam>(PlayerState);
	if (Player_State != nullptr)
	{
		if (Player_State->Team == Cast<APlayerStatisticTeam>(GetOwningPlayerState())->Team)
		{
			ColorBorder->SetBrushColor(OurTeam.GetSpecifiedColor());
		}
		else
		{
			ColorBorder->SetBrushColor(OppositeTeam.GetSpecifiedColor());
		}
	}
}
