// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "E_GameState.generated.h"




UENUM(BlueprintType)
enum class E_GameState : uint8
{
	PreStart,
	Game,
	EndGame
}; 


