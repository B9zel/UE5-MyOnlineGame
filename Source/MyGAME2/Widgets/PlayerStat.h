// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerStat.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME2_API UPlayerStat : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		class UTextBlock* NickName;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		class UTextBlock* Deaths;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		class UTextBlock* Kills;


	class APlayerStatistic* PlayerState;

public:

	virtual void NativeConstruct() override;
	UFUNCTION()
	FText BindNickName();
	UFUNCTION()
	FText BindDeaths();
	UFUNCTION()
	FText BindKills();
};
