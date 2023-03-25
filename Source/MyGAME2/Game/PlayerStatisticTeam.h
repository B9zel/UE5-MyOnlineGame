// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <MyGAME2/Game/PlayerStatistic.h>
#include "PlayerStatisticTeam.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME2_API APlayerStatisticTeam : public APlayerStatistic
{
	GENERATED_BODY()
public:
	UPROPERTY(Replicated,BlueprintReadWrite)
	TEnumAsByte<enum E_Team> Team;


protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	E_Team GetRandomTeam();
	UFUNCTION(BlueprintCallable)
	E_Team GetBalansedSelectTeam(TEnumAsByte<enum E_Team> SetTeam);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	UFUNCTION()
		void OnStartRound();
};
