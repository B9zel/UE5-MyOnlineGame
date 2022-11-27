// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Base_GameMode.generated.h"

//UDELIGATE();
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTestDelegate);
 
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

public:

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
		  void Pawn_Dead(APlayerController* DeadPlayer, APlayerController* DeathInstigator);

	UFUNCTION()
		virtual AGame_Spectator* Spawn_Spectator(class APlayerController* Player, class APlayerController* DeadInstigator);
	// Implementation in Blueprint
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		 ABaseTank* Spawn_Player(APlayerController* PlayerController, TSubclassOf<class AActor> SpawnClass);

	UFUNCTION(BlueprintNativeEvent)
		 void StartRound();

	UFUNCTION(BlueprintCallable)
		  virtual void UpdateDeathPoints(APlayerController* DeadPlayer, APlayerController* DeathInstigatorPlayer);

	UFUNCTION(BlueprintCallable)
		virtual void StopRound();

	UFUNCTION(NetMulticast, Unreliable)
		void StopRoundOnClient(APlayerController* PlayerController);

	UFUNCTION()
		void RechedTimeLimit();
};
