// Fill out your copyright notice in the Description page of Project Settings.


#include "Game_Interface.h"
#include <Components/CanvasPanel.h>
#include "Widget_HP.h"
#include "Widget_Reload.h"
#include "BaseTank.h"
#include "PawnController.h"



void UGame_Interface::NativeConstruct()
{
	Super::NativeConstruct();

	ABaseTank* Pawn = Cast<ABaseTank>(GetOwningPlayerPawn());
	if (Pawn != nullptr)
	{
		Pawn->Main_Widget = this;
	}
}
