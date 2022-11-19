// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StatisticsMenu.generated.h"



UCLASS()
class MYGAME2_API UStatisticsMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> UserWidget;

	class ABaseGameState* Game_State;
protected:
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		class UW_RoundTime* RoundTime;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		class UVerticalBox* VB_Player;
public:
	UFUNCTION()
	virtual void NativeConstruct() override;

	ABaseGameState* GetBaseGameState();
	
	virtual UVerticalBox* GetPlayerList(APlayerState* PlayerStat);

	UFUNCTION()
	virtual void UpdatePlayerList();
};
