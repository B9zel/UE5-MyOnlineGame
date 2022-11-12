// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_Spectator.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME2_API UW_Spectator : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UW_RoundTime* TimerOfRound;
};
