// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <MyGAME2/Widgets/EndRound/W_ResultsEndRound.h>
#include "W_TeamResultsEndRound.generated.h"



UCLASS()
class MYGAME2_API UW_TeamResultsEndRound : public UW_ResultsEndRound
{
	GENERATED_BODY()

protected:

	virtual void InitializeTextResult() override;
};
