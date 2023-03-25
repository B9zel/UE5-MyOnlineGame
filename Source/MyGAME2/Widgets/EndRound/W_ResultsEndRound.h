// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_ResultsEndRound.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME2_API UW_ResultsEndRound : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UBorder* B_ResultsRound;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UTextBlock* T_Winner;
	
public:
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		 class UW_EndRoundMapVote* EndRoundMap;
private:

	virtual void NativeConstruct() override;

	virtual void InitializeTabResults();

	virtual void InitializeTextResult();
};
