// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Base_GameMode.generated.h"

//UDELIGATE();
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTestDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDispatchOneParam,ABaseTank*, Pawn);
 
UCLASS()
class MYGAME2_API ABase_GameMode : public AGameModeBase
{
	GENERATED_BODY()
//	GENERATED_UCLASS_BODY()
public:

	ABase_GameMode();

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class AActor> Spectator_Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool AutoRespawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool LimiyByTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTimespan TimeLimit;

	UPROPERTY(BlueprintAssignable)
		FTestDelegate RoundStart;

	UPROPERTY(BlueprintAssignable)
		FTestDelegate RoundEnded;
	UPROPERTY(BlueprintAssignable)
		FTestDelegate DSpawnSpectator;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
		FTestDelegate DSpawnTank;
	

public:

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
		  void Pawn_Dead(APlayerController* DeadPlayer, APlayerController* DeathInstigator);

	UFUNCTION()
		virtual void SpawnSpectator(class APlayerController* Player, class APlayerController* DeadInstigator);

	// Implementation in Blueprint
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		 ABaseTank* Spawn_Player(APlayerController* PlayerController, TSubclassOf<class AActor> SpawnClass);

	UFUNCTION(BlueprintNativeEvent)
		 void StartRound();

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
		  void UpdateDeathPoints(APlayerController* DeadPlayer, APlayerController* DeathInstigatorPlayer);

	UFUNCTION(BlueprintCallable)
		virtual void StopRound();

	UFUNCTION()
		void RechedTimeLimit();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable,BlueprintPure)
	bool ShouldDamagePlayer(APlayerController* Player, APlayerController* InstigatorPLayer);
};
