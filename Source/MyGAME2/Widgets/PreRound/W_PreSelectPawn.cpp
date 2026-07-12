// Fill out your copyright notice in the Description page of Project Settings.


#include "W_PreSelectPawn.h"
#include <Components/Button.h>
#include "../../PawnController.h"
#include "../../BaseTank.h"


void UW_PreSelectPawn::NativeConstruct()
{
	Super::NativeConstruct();

	if (!Controller)
	{
		Controller = Cast<APawnController>(GetOwningPlayer());
	}

	B_SelectPawn->OnClicked.AddDynamic(this, &UW_PreSelectPawn::OnClickSelectPawn);
	HasDisable = false;
}

void UW_PreSelectPawn::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);


	if (!B_SelectPawn->GetIsEnabled())
	{
		if (Controller && !HasDisable)
		{
			Controller->SetSpawnPawn(SelectionPawn);
			HasDisable = true;
		}
	}
	else
	{
		HasDisable = false;
	}
}

void UW_PreSelectPawn::OnClickSelectPawn()
{
	D_Select.Broadcast(E_Pawn);
}
