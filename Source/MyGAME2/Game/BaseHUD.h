// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BaseHUD.generated.h"



UCLASS()
class MYGAME2_API ABaseHUD : public AHUD
{
	GENERATED_BODY()
	
public:

	void ToggleHUD(bool isShow);

	void ToggleTab(bool isShow);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UStatisticsMenu> TabWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UGame_Interface> HUDWidgetClass;

	class UStatisticsMenu* TabWidget;
	class UGame_Interface* HUDWidget;
};
