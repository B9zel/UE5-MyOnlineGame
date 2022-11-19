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

	~ABaseHUD();

	virtual void BeginPlay() override;

	void ToggleHUD(bool isShow);

	void ToggleTab(bool isShow);

	void ToggleSpectatorHUD(bool isShow);
	UFUNCTION()
	void OnRoundStarted();

	UFUNCTION()
	UGame_Interface* GetHUDWidget();
	UFUNCTION()
	UStatisticsMenu* GetTabWidget();
	UFUNCTION()
	void OnPlayerAlive();
	UFUNCTION()
	void OnPlayerDead(ABaseTank* DeathInstigator);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UStatisticsMenu> TabWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UGame_Interface> HUDWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UW_Spectator> SpectatorWidgetClass;
private:

	class UStatisticsMenu* TabWidget;
	class UGame_Interface* HUDWidget;
	class UW_Spectator* SpectatorWidget;
};
