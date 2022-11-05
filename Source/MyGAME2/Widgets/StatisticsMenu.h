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

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UTextBlock* Timer;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UVerticalBox* VB_PlayerState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> UserWidget;

	class ABaseGameState* Game_State;

public:
	
	
	virtual void NativeConstruct() override;
	ABaseGameState* GetBaseGameState();

	void UpdatePlayerList();

	UFUNCTION()
	FText UpdateTimerTick();
};
