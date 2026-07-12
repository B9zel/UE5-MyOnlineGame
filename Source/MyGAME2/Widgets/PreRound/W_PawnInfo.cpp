// Fill out your copyright notice in the Description page of Project Settings.


#include "W_PawnInfo.h"
#include <Components/WidgetSwitcher.h>
#include <Components/TextBlock.h>
#include "Internationalization/TextTransformer.h" 
#include <Kismet/KismetTextLibrary.h>
#include "../../Pawns/HeavyTank.h"
#include "../../Pawns/Light_Tank.h"
#include "../../Pawns/Medium_Tank.h"
#include "../../Pawns/Stealth_Tank.h"
#include "../../Data/DataAssets/BaseTankConfigDataAsset.h"





void UW_PawnInfo::SelectTankConfig(const E_AllPawns& TypeTank)
{
	if (PawnsInfo.Contains(TypeTank))
	{
		UpdateTextProperties(*PawnsInfo.Find(TypeTank));
	}
}

void UW_PawnInfo::UpdateTextProperties(const UBaseTankConfigDataAsset* Config)
{
	if (!Config) return;

	FNumberFormattingOptions NumberOptions;
	NumberOptions.AlwaysSign = false;
	NumberOptions.UseGrouping = true;
	NumberOptions.MinimumIntegralDigits = 1;
	NumberOptions.MaximumIntegralDigits = 324;
	NumberOptions.MinimumFractionalDigits = 0;
	NumberOptions.MaximumFractionalDigits = 2;

	TB_NamePawn->SetText(Config->Name);
	TB_Speed->SetText(FText::AsNumber(Config->Speed, &NumberOptions));
	TB_RotationSpeed->SetText(FText::AsNumber(Config->RotationSpeed, &NumberOptions));
	TB_TowerRotationSpeed->SetText(FText::AsNumber(Config->TowerRotationSpeed, &NumberOptions));
	TB_Damage->SetText(FText::AsNumber(Config->Damage, &NumberOptions));
	TB_HP->SetText(FText::AsNumber(Config->HealthPoints, &NumberOptions));
	TB_TimeReload->SetText(FText::AsNumber(Config->TimeReload, &NumberOptions));
	TB_SkillDescription->SetText(Config->SkillDescription);
	TB_SkillTimeReload->SetText(FText::AsNumber(Config->SkillTimeReload, &NumberOptions));
	TB_SkillTimeUse->SetText(FText::AsNumber(Config->SkillTimeUse, &NumberOptions));
}
