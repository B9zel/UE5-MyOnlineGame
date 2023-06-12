// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "BaseSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME2_API UBaseSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:


	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float SensetiveX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SensetiveY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Nickname;
};
