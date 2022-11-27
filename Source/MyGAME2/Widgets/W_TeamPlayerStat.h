// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <MyGAME2/Widgets/PlayerStat.h>
#include "W_TeamPlayerStat.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME2_API UW_TeamPlayerStat : public UPlayerStat
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;

private:

	void SetColorTeam(FSlateColor OurTeam, FSlateColor OppositeTeam);

public:
	UPROPERTY(Editanywhere, BlueprintReadWrite)
		FSlateColor OurTeamColor;
	UPROPERTY(Editanywhere, BlueprintReadWrite)
		FSlateColor OppositeTeamColor;
};
