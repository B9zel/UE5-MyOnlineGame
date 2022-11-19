// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_SpectateInfoKill.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME2_API UW_SpectateInfoKill : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UTextBlock* NameKiller;

public:

	UFUNCTION()
	void SetKilledInfo(APlayerStatistic* PlayerState);

};
