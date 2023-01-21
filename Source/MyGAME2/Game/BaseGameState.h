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

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	class UChatComponent* chatComponent;

	//UPROPERTY(BlueprintAssignable)
	//	FDelegate TimeEnded;
	UPROPERTY(BlueprintAssignable)
		FDelegate RoundEnded;
	UPROPERTY(BlueprintAssignable)
		FDelegate RoundStarted;

	UPROPERTY(ReplicatedUsing = OnRep_RoundInProgress,BlueprintReadWrite)
		TEnumAsByte<enum E_GameState> RoundInProgress;
	UPROPERTY(EditAnywhere)
		uint16 playerInSession;
	
protected:

	class ABase_GameMode* GameMode;

	UPROPERTY(Replicated, BlueprintReadWrite)
		FTimespan RoundTime;
	UPROPERTY(Replicated,BlueprintReadWrite)
		FTimespan PreStartRoundTimer;

protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:

	void TickRoundTime();
	UFUNCTION()
	void OnRoundEnded();
	
	void TickPreRoundTime();

	UFUNCTION(NetMulticast,Reliable)
	void RoundEnd_Multicast();

	UFUNCTION()
	void OnRep_RoundInProgress();

	UFUNCTION()
	void OnRoundStarted();

	FTimespan GetRoundTime();

	FTimespan GetPreStartRoundTime();
};
