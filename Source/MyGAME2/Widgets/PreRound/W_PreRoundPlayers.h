// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_PreRoundPlayers.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME2_API UW_PreRoundPlayers : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* VB_Players;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<class UW_PreRoundPlayer> WPreRoundPlayerClass;

protected:

	virtual void NativeConstruct() override;

private:

	void UpdatePlayerName();
};
