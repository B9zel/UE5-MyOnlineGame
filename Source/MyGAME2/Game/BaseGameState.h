// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "BaseGameState.generated.h"

//UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateOneParam,ABaseTank*,Pawn);

UCLASS()
class MYGAME2_API ABaseGameState : public AGameStateBase
{
	GENERATED_BODY()

public:

	ABaseGameState();

	UPROPERTY(EditAnywhere)
	class UChatComponent* chatComponent;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UVoteComponent* voteComponent;

	//UPROPERTY(BlueprintAssignable)
	//	FDelegate TimeEnded;
	UPROPERTY(BlueprintAssignable)
		FDelegate RoundEnded;
	UPROPERTY(BlueprintAssignable)
		FDelegate RoundStarted;
	UPROPERTY(BlueprintAssignable)
		FDelegate PreRoundStarted;
	UPROPERTY(BlueprintAssignable)
		FDelegate DSpawnSpectator;
	UPROPERTY(BlueprintAssignable)
		FDelegate DSpawnTank;

	UPROPERTY(ReplicatedUsing = OnRep_RoundInProgress,BlueprintReadWrite)
		TEnumAsByte<enum E_GameState> RoundInProgress;
	UPROPERTY(EditAnywhere)
		uint16 playerInSession;
	
protected:

	class ABase_GameMode* GameMode;

	UPROPERTY(Replicated, BlueprintReadWrite,EditAnywhere)
		FTimespan RoundTime;
	UPROPERTY(Replicated,BlueprintReadWrite, EditAnywhere)
		FTimespan PreStartRoundTimer;

protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	UFUNCTION()
	void OpenNexpMap(FName MapName);
	UFUNCTION()
	void SpawnSpectatorOnServer();
	UFUNCTION(NetMulticast, Unreliable)
	void SpawnSpectatorMulticast();
	UFUNCTION(NetMulticast, Unreliable)
	void SpawnTankMulticast();

public:

	virtual void TickRoundTime();
	UFUNCTION()
	void OnRoundEnded();
	
	virtual void TickPreRoundTime();

	UFUNCTION(NetMulticast,Reliable)
	void RoundEnd_Multicast();

	UFUNCTION()
	void OnRep_RoundInProgress();

	UFUNCTION()
	void OnRoundStarted();

	FTimespan GetRoundTime();

	FTimespan GetPreStartRoundTime();
};
