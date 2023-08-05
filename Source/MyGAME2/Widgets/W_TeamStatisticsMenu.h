// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <MyGAME2/Widgets/StatisticsMenu.h>
#include "W_TeamStatisticsMenu.generated.h"



UCLASS()
class MYGAME2_API UW_TeamStatisticsMenu : public UStatisticsMenu
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UVerticalBox* VB_PlayerOwn;

public:

	virtual UVerticalBox* GetPlayerList(APlayerState* PlayerState) override;
	virtual void UpdatePlayerList() override;
};
