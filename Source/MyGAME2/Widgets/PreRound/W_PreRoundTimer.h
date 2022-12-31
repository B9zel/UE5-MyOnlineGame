// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_PreRoundTimer.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME2_API UW_PreRoundTimer : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UTextBlock* Timer;
private:
	class ABaseGameState* Game_State;

private:

	virtual void NativeConstruct() override;

	UFUNCTION()
		FText UpdateTimerTick();
};
