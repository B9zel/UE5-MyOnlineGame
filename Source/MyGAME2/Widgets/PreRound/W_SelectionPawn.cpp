// Fill out your copyright notice in the Description page of Project Settings.


#include "W_SelectionPawn.h"
#include "W_PreSelectPawn.h"
#include "W_PawnInfo.h"
#include <Components/Button.h>



void UW_SelectionPawn::NativeConstruct()
{
	Super::NativeConstruct();

	W_HeavyTank->D_Select.AddDynamic(this, &UW_SelectionPawn::OnSelectedPawn);
	W_LightTank->D_Select.AddDynamic(this, &UW_SelectionPawn::OnSelectedPawn);
	W_MediumTank->D_Select.AddDynamic(this, &UW_SelectionPawn::OnSelectedPawn);
	W_StelsTank->D_Select.AddDynamic(this, &UW_SelectionPawn::OnSelectedPawn);

}

void UW_SelectionPawn::OnSelectedPawn(E_AllPawns pawn)
{
	W_Info->SetSwitchInfo(pawn);
	switch (pawn)
	{
	case LightTank:
		W_LightTank->B_SelectPawn->SetIsEnabled(false);
		W_HeavyTank->B_SelectPawn->SetIsEnabled(true);
		W_MediumTank->B_SelectPawn->SetIsEnabled(true);
		W_StelsTank->B_SelectPawn->SetIsEnabled(true);
		break;
	case MediumTank:
		W_MediumTank->B_SelectPawn->SetIsEnabled(false);
		W_HeavyTank->B_SelectPawn->SetIsEnabled(true);
		W_LightTank->B_SelectPawn->SetIsEnabled(true);
		W_StelsTank->B_SelectPawn->SetIsEnabled(true);
		break;
	case HeavyTank:
		W_HeavyTank->B_SelectPawn->SetIsEnabled(false);
		W_LightTank->B_SelectPawn->SetIsEnabled(true);
		W_MediumTank->B_SelectPawn->SetIsEnabled(true);
		W_StelsTank->B_SelectPawn->SetIsEnabled(true);
		break;
	case StelsTank:
		W_StelsTank->B_SelectPawn->SetIsEnabled(false);
		W_HeavyTank->B_SelectPawn->SetIsEnabled(true);
		W_MediumTank->B_SelectPawn->SetIsEnabled(true);
		W_LightTank->B_SelectPawn->SetIsEnabled(true);
		break;
	case TotalPawns:
		break;
	default:
		break;
	}
}

