
#include "VoteComponent.h"
#include <Net/UnrealNetwork.h>
#include <Engine/DataTable.h>
#include <Kismet/KismetMathLibrary.h>
#include <Kismet/GameplayStatics.h>
#include <GameFramework/GameState.h>
#include "../../Data/ST_MapInfo.h"


UVoteComponent::UVoteComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.TickInterval = 1.0f;
	

	MaxVoteMap = 0;
}


// Called when the game starts
void UVoteComponent::BeginPlay()
{
	Super::BeginPlay();
	
	SetIsReplicated(true);
	RegisterComponent();
}


// Called every frame
void UVoteComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UE_LOG(LogTemp, Error, TEXT("Event tick Active"));
	voteMapTime--;
	if (voteMapTime <= 0)
	{
		StopVote();
	}
}

void UVoteComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UVoteComponent, voteInProgress);
	DOREPLIFETIME(UVoteComponent, voteMapTime);
	DOREPLIFETIME(UVoteComponent, ArrMap);
	DOREPLIFETIME(UVoteComponent, VotedMap);
	DOREPLIFETIME(UVoteComponent, ArrPlayersVotes);
	DOREPLIFETIME(UVoteComponent, MaxVoteMap);
}

void UVoteComponent::StartVote()
{
	SetComponentTickEnabled(true);
	ChooseMatVote();
	voteInProgress = true;
	VoteStarted.Broadcast();
}

void UVoteComponent::StopVote()
{
	SetComponentTickEnabled(false);
	voteInProgress = false;
	VoteEnded.Broadcast(FName(GetMaxVoteMap()));
}

void UVoteComponent::OnRep_voteInProgress()
{
	if (voteInProgress)
	{
		VoteStarted.Broadcast();
	}
	else
	{
		VoteEnded.Broadcast(FName(GetMaxVoteMap()));
	}
}

void UVoteComponent::OnRep_ArrMap()
{
	OnCreateToVoteMap.Broadcast(ArrMap);
}

void UVoteComponent::ChooseMatVote()
{
	TArray<FName> arrRowName = DataTable->GetRowNames();

	for (int i = 0; i < NumberMaps; i++)
	{
		if (arrRowName.Num() > 0)
		{
			int RandomIndex = UKismetMathLibrary::RandomInteger(arrRowName.Num());
			ArrMap.Add(arrRowName[RandomIndex]);
			arrRowName.RemoveAt(RandomIndex);
		}
	}

}

int UVoteComponent::GetSelectedMapVote()
{
	int MaxValue;
	TArray<int> arrVoteMapIndex, arrMapVotes;
	arrVoteMapIndex.SetNum(1);
	
	for (int i = 0; i < ArrMap.Num(); i++)
	{
		arrMapVotes.Add(GetMapVote(i));
	}

	UKismetMathLibrary::MaxOfIntArray(arrMapVotes, arrVoteMapIndex[0], MaxValue);
	for (int i = 0; i < arrMapVotes.Num(); i++)
	{
		if (arrMapVotes[i] == arrMapVotes[arrVoteMapIndex[0]] && i != arrVoteMapIndex[0])
		{
			arrVoteMapIndex.Add(i);
		}
	}
	return arrVoteMapIndex[UKismetMathLibrary::RandomInteger(arrVoteMapIndex.Num())];
}

void UVoteComponent::SetVote(APlayerState* player, int MapIndex)
{
	AGameStateBase* GameState = GetOwner<AGameStateBase>();
	if (ArrPlayersVotes.IsValidIndex(GameState->PlayerArray.Find(player)))
	{
		ArrPlayersVotes[GameState->PlayerArray.Find(player)] = MapIndex;
	}
	else
	{
		ArrPlayersVotes.Insert(MapIndex, GameState->PlayerArray.Find(player));
	}

	MaxVoteMap = GetSelectedMapVote();
}

FString UVoteComponent::GetMaxVoteMap()
{
	if (ArrMap.IsValidIndex(MaxVoteMap))
	{
		FName string = DataTable->FindRow<FST_MapInfo>(ArrMap[MaxVoteMap], "")->NameMap;
		return string.ToString();
	}
	else
	{
		return FString("");
	}
}

int UVoteComponent::GetMapVote(int MapIndex)
{
	int Votes = 0;
	for (int &el : ArrPlayersVotes)
	{
		if (el == MapIndex)
		{
			Votes++;
		}
	}
	return Votes;
}

