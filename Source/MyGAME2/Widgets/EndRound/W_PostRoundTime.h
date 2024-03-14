// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../W_RoundTime.h"
#include "W_PostRoundTime.generated.h"




UCLASS()
class MYGAME2_API UW_PostRoundTime : public UW_RoundTime
{
	GENERATED_BODY()
protected:
	UFUNCTION()
	virtual void NativeConstruct() override;

	virtual FText UpdateTimerTick() override;

	UFUNCTION()
	FText UpdateNextMap();

protected:
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UTextBlock* T_NextMap;

public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FText TextNextMap = NSLOCTEXT("PostRound", "K_NextMap", "Next map is ");
	
};
