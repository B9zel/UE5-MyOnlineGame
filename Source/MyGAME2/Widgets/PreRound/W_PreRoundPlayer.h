// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_PreRoundPlayer.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME2_API UW_PreRoundPlayer : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* PlayerName;

	class APlayerState* PlayerState;
protected:

	virtual void NativeConstruct() override;

	UFUNCTION()
	FText BindPlayerName();
};
