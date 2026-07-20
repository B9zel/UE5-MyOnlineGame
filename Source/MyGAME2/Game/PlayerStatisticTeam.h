// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <MyGAME2/Game/PlayerStatistic.h>
#include "PlayerStatisticTeam.generated.h"


enum class E_Team : uint8;

UCLASS()
class MYGAME2_API APlayerStatisticTeam : public APlayerStatistic
{
	GENERATED_BODY()

public:

	UPROPERTY(Replicated,BlueprintReadWrite)
	E_Team Team;

protected:

	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	UFUNCTION()
		void OnStartRound();

	UFUNCTION()
	E_Team GetRandomTeam();
public:
	UFUNCTION(BlueprintCallable)
	E_Team GetBalansedSelectTeam(E_Team SetTeam);

	
};
