// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "VoteComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FD_Vote);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FD_VoteParam,FName,NameMap);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FD_VoteOneParam,TArray<FName>,MapNames);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYGAME2_API UVoteComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UVoteComponent();
	UFUNCTION()
	virtual void StartVote();
	virtual void StopVote();

	void ChooseMatVote();
	int GetSelectedMapVote();

	void SetVote(APlayerState* player, int MapIndex);
	FString GetMaxVoteMap();
	FString GetShowNameMapWithMaxVote();

	int GetMapVote(int MapIndex);
protected:

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
		void OnRep_voteInProgress();
	UFUNCTION()
		void OnRep_ArrMap();

protected:
	UPROPERTY(ReplicatedUsing = OnRep_voteInProgress)
	bool voteInProgress;
	UPROPERTY(EditAnywhere)
	int NumberMaps;
	UPROPERTY(Replicated)
	int VotedMap;
	UPROPERTY(ReplicatedUsing = OnRep_ArrMap)
	TArray<FName> ArrMap;
	UPROPERTY(Replicated)
	TArray<int> ArrPlayersVotes;

public:
	UPROPERTY(EditAnywhere, Replicated)
	int voteMapTime;
	UPROPERTY(EditAnywhere)
	class UDataTable* DataTable;
	UPROPERTY(Replicated)
	int MaxVoteMap;


	FD_Vote VoteStarted;
	FD_VoteParam VoteEnded;
	FD_VoteOneParam OnCreateToVoteMap;
};