// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <MyGAME2/Game/BaseGameState.h>
#include "TeamGameState.generated.h"



UCLASS()
class MYGAME2_API ATeamGameState : public ABaseGameState
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<TEnumAsByte<enum E_Team>, int> TeamPoints;
	UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere)
	TArray<int> PointsArray;

public:

	ATeamGameState();

	int GetPoints(E_Team Team);

	UFUNCTION(BlueprintCallable)
	void ChangetTeamPoints(E_Team Team, int Value);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;
};
