// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_PreRound.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME2_API UW_PreRound : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UW_SelectionPawn* W_SelectionPawn;
};
