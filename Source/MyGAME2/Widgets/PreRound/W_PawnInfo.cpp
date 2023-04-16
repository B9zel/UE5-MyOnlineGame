// Fill out your copyright notice in the Description page of Project Settings.


#include "W_PawnInfo.h"
#include <Components/WidgetSwitcher.h>
#include <Components/TextBlock.h>

#include "../../Pawns/HeavyTank.h"
#include "../../Pawns/Light_Tank.h"
#include "../../Pawns/Medium_Tank.h"
#include "../../Pawns/Stels_Tank.h"


void UW_PawnInfo::SetSwitchInfo(E_AllPawns E_pawm)
{
	switch (E_pawm)
	{
	case LightTank:
		InfoForPawn->SetText(*PawnsInfo.Find(E_AllPawns::LightTank));
		//WS_Info->SetActiveWidgetIndex(E_AllPawns::LightTank);
		break;
	case MediumTank:
		InfoForPawn->SetText(*PawnsInfo.Find(E_AllPawns::MediumTank));
		//WS_Info->SetActiveWidgetIndex(E_AllPawns::LightTank);
		break;
	case HeavyTank:
		InfoForPawn->SetText(*PawnsInfo.Find(E_AllPawns::HeavyTank));
		//WS_Info->SetActiveWidgetIndex(E_AllPawns::LightTank);
		break;
	case StelsTank:
		InfoForPawn->SetText(*PawnsInfo.Find(E_AllPawns::StelsTank));
		//WS_Info->SetActiveWidgetIndex(E_AllPawns::LightTank);
		break;
	case TotalPawns:
		break;
	default:
		break;
	}
}

void UW_PawnInfo::NativeConstruct()
{
	Super::NativeConstruct();

	PawnsInfo.Add(E_AllPawns::LightTank, FText::FromString(GetLightTankInfo()));
	PawnsInfo.Add(E_AllPawns::HeavyTank, FText::FromString(GetHeavyTankInfo()));
	PawnsInfo.Add(E_AllPawns::MediumTank, FText::FromString(GetMediumTankInfo()));
	PawnsInfo.Add(E_AllPawns::StelsTank, FText::FromString(GetStelsTankInfo()));

}

FString UW_PawnInfo::GetLightTankInfo()
{
	FString Info;
	ALight_Tank* pawn = GetWorld()->SpawnActor<ALight_Tank>(ALight_Tank::StaticClass(), FVector(0, 0, -500),FRotator(0,0,0));

	if (pawn != nullptr)
	{
		Info = "\t\t\tLight tank"
			"\nSpeed: " + FString::FromInt(pawn->GetSpeed()) +
			"\nRotation speed: " + FString::FromInt(pawn->GetRotationSpeed()) +
			"\nTower rotation speed: " + FString::FromInt(pawn->GetTowerRotationSpeed()) +
			"\nDamage: " + FString::FromInt(pawn->GetDamage()) +
			"\nHealth points(HP): " + FString::FromInt(pawn->GetHP()) +
			"\nTime reload: " + FString::FromInt(pawn->GetTimeReload()) + " seconds" +
			"\n\nSkill: Up tank speed" +
			"\nSkill time reload: " + FString::FromInt(pawn->GetTimeReloadSuperPower()) + " seconds" +
			"\nSkill time use: " + FString::FromInt(pawn->GetTimeUseSuperPower()) + " seconds";
	
		pawn->Destroy();
	}
	
	return Info;
}

FString UW_PawnInfo::GetMediumTankInfo()
{
	FString Info;
	AMedium_Tank* pawn = GetWorld()->SpawnActor<AMedium_Tank>(AMedium_Tank::StaticClass(), FVector(0, 0, -500), FRotator(0, 0, 0));

	if (pawn != nullptr)
	{
		Info = "\t\t\tMedium tank"
			"\nSpeed: " + FString::FromInt(pawn->GetSpeed()) +
			"\nRotation speed: " + FString::FromInt(pawn->GetRotationSpeed()) +
			"\nTower rotation speed: " + FString::FromInt(pawn->GetTowerRotationSpeed()) +
			"\nDamage: " + FString::FromInt(pawn->GetDamage()) +
			"\nHealth points(HP): " + FString::FromInt(pawn->GetHP()) +
			"\nTime reload: " + FString::FromInt(pawn->GetTimeReload()) + " seconds" + 
			"\n\nSkill: Immunity to attacks" +
			"\nSkill time reload: " + FString::FromInt(pawn->GetTimeReloadSuperPower()) + " seconds" +
			"\nSkill time use: " + FString::FromInt(pawn->GetTimeUseSuperPower()) + " seconds";

		pawn->Destroy();
	}
	return Info;
}

FString UW_PawnInfo::GetStelsTankInfo()
{
	FString Info;
	AStels_Tank* pawn = GetWorld()->SpawnActor<AStels_Tank>(AStels_Tank::StaticClass(), FVector(0, 0, -500), FRotator(0, 0, 0));

	if (pawn != nullptr)
	{
		Info = "\t\t\tStels tank"
			"\nSpeed: " + FString::FromInt(pawn->GetSpeed()) +
			"\nRotation speed: " + FString::FromInt(pawn->GetRotationSpeed()) +
			"\nTower rotation speed: " + FString::FromInt(pawn->GetTowerRotationSpeed()) +
			"\nDamage: " + FString::FromInt(pawn->GetDamage()) +
			"\nHealth points(HP): " + FString::FromInt(pawn->GetHP()) +
			"\nTime reload: " + FString::FromInt(pawn->GetTimeReload()) + " seconds" +
			"\n\nSkill: Invisibility" +
			"\nSkill time reload: " + FString::FromInt(pawn->GetTimeReloadSuperPower()) + " seconds" +
			"\nSkill time use: " + FString::FromInt(pawn->GetTimeUseSuperPower()) + " seconds";

		pawn->Destroy();
	}
	return Info;
}

FString UW_PawnInfo::GetHeavyTankInfo()
{
	FString Info;
	AHeavyTank* pawn = GetWorld()->SpawnActor<AHeavyTank>(AHeavyTank::StaticClass(), FVector(0, 0, -500), FRotator(0, 0, 0));

	if (pawn != nullptr)
	{
		Info = "\t\t\tHeavy tank"
			"\nSpeed: " + FString::FromInt(pawn->GetSpeed()) +
			"\nRotation speed: " + FString::FromInt(pawn->GetRotationSpeed()) +
			"\nTower rotation speed: " + FString::FromInt(pawn->GetTowerRotationSpeed()) +
			"\nDamage: " + FString::FromInt(pawn->GetDamage()) +
			"\nHealth points(HP): " + FString::FromInt(pawn->GetHP()) +
			"\nTime reload: " + FString::FromInt(pawn->GetTimeReload()) + " seconds" +
			"\n\nSkill: Next attack with up damage" +
			"\nSkill time reload: " + FString::FromInt(pawn->GetTimeReloadSuperPower()) + " seconds" +
			"\nSkill damage: " + FString::FromInt(pawn->GetSuperDamage());

		pawn->Destroy();
	}
	return Info;
}