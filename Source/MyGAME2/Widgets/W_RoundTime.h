// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_RoundTime.generated.h"




UCLASS()
class MYGAME2_API UW_RoundTime : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		class UTextBlock* Timer;

	class ABaseGameState* Game_State;

public:
	
	virtual void NativeConstruct() override;

	UFUNCTION()
	virtual FText UpdateTimerTick();
};
