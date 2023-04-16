// Fill out your copyright notice in the Description page of Project Settings.


#include "W_PreSelectPawn.h"
#include <Components/Button.h>
#include "../../PawnController.h"
#include "../../BaseTank.h"


void UW_PreSelectPawn::NativeConstruct()
{
	Super::NativeConstruct();

	B_SelectPawn->OnClicked.AddDynamic(this, &UW_PreSelectPawn::OnClickSelectPawn);



}

void UW_PreSelectPawn::OnClickSelectPawn()
{
	APawnController* Controller = GetOwningPlayer<APawnController>();

	if (Controller != nullptr)
	{
		Controller->SetSpawnPawn(SelectionPawn);
	}


	D_Select.Broadcast(E_Pawn);
}
