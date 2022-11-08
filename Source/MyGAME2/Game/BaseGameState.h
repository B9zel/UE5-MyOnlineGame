// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "BaseGameState.generated.h"

//UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDelegate);

UCLASS()
class MYGAME2_API ABaseGameState : public AGameStateBase
{
	GENERATED_BODY()

public:

	ABaseGameState();

	virtual void BeginPlay() override;

	UPROPERTY(Replicated, BlueprintReadWrite)
		FTimespan RoundTime;
	
	class ABase_GameMode* GameMode;
	
	UPROPERTY(BlueprintAssignable)
		FDelegate TimeEnded;

	UPROPERTY(BlueprintAssignable)
		FDelegate RoundEnded;
	UPROPERTY(BlueprintAssignable)
		FDelegate RoundStarted;
	UPROPERTY(ReplicatedUsing = OnRep_OnRoundInProgress,BlueprintReadWrite)
		bool RoundInProgress;
	UPROPERTY()
		FTimerHandle Timer;

public:

	void StartRoundTimer();

	void TickRoundTime();
	UFUNCTION()
	void OnRoundEnded();
	
	UFUNCTION(NetMulticast,Reliable)
	void RoundEnd_Multicast();

	UFUNCTION()
	void OnRoundStarted();
	UFUNCTION()
	void OnRep_OnRoundInProgress();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
