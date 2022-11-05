// Fill out your copyright notice in the Description page of Project Settings.


#include "Game_Interface.h"
#include <Components/CanvasPanel.h>
#include "Widget_HP.h"
#include "Widget_Reload.h"
#include "BaseTank.h"
#include "PawnController.h"

void UGame_Interface::Take_Ref(class ABaseTank* pawn)
{
	//pawn->Main_Widget = this;
	Cast<ABaseTank>(GetOwningPlayer()->GetPawn())->Main_Widget = this;
	//Cast<APawnController>(GetOwningPlayer())->Game_Interface = this;
}