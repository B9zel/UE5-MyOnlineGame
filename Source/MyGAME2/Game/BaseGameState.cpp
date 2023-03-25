
#include "BaseGameState.h"
#include <Net/UnrealNetwork.h>
#include "Base_GameMode.h"
#include <Kismet/GameplayStatics.h>
#include <MyGAME2/PawnController.h>
#include <MyGAME2/Widgets/StatisticsMenu.h>
#include "../Enums/E_GameState.h"
#include "Components/ChatComponent.h"
#include "Components/VoteComponent.h"


ABaseGameState::ABaseGameState()
{
	this->PrimaryActorTick.bCanEverTick = true;
	this->PrimaryActorTick.TickInterval = 1.0f;

	chatComponent = CreateDefaultSubobject<UChatComponent>(TEXT("Chat Component"));

	voteComponent = CreateDefaultSubobject<UVoteComponent>(TEXT("Vote Component"));
	RoundInProgress = E_GameState::PreStart;
	playerInSession = 2;
	

}

void ABaseGameState::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		SetReplicates(true);
		GameMode = Cast<ABase_GameMode>(UGameplayStatics::GetGameMode(this));

		if (GameMode != nullptr)
		{
			GameMode->RoundEnded.AddDynamic(this, &ABaseGameState::OnRoundEnded);
			
			//GameMode->RoundStart.AddDynamic(this, &ABaseGameState::OnRoundStarted);
		}
	}
}

void ABaseGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		switch (RoundInProgress)
		{
		case PreStart:
			TickPreRoundTime();
			break;
		case Game:
			TickRoundTime();
			break;
		case EndGame:
			break;
		default:
			break;
		}
	}
}


void ABaseGameState::TickRoundTime()
{
	RoundTime += FTimespan::FromSeconds(1.0f);

	if (GameMode->TimeLimit <= RoundTime && RoundInProgress == E_GameState::Game)
	{
		Cast<ABase_GameMode>(UGameplayStatics::GetGameMode(this))->RechedTimeLimit();
	}
	
}


void ABaseGameState::TickPreRoundTime()
{
	if (PlayerArray.Num() >= playerInSession)
	{
		PreStartRoundTimer -= FTimespan::FromSeconds(1.0f);
		if (PreStartRoundTimer.GetTotalSeconds() <= 0 && RoundInProgress == E_GameState::PreStart)
		{
			Cast<ABase_GameMode>(UGameplayStatics::GetGameMode(this))->StartRound();
			RoundInProgress = E_GameState::Game;
			RoundStarted.Broadcast();
		}
	}
	else
	{
		PreStartRoundTimer = FTimespan::FromSeconds(10);
	}
	
}

void ABaseGameState::RoundEnd_Multicast_Implementation()
{
	RoundEnded.Broadcast();
}

void ABaseGameState::OnRep_RoundInProgress()
{
	switch (RoundInProgress)
	{
	case E_GameState::PreStart:
		break;
	case E_GameState::Game:
		RoundStarted.Broadcast();
		break;
	case E_GameState::EndGame:

	default:
		break;
	}
}


void ABaseGameState::OnRoundStarted()
{
}


void ABaseGameState::OnRoundEnded()
{
	RoundInProgress = E_GameState::EndGame;
	RoundEnd_Multicast();
	voteComponent->StartVote();
	voteComponent->VoteEnded.AddDynamic(this, &ABaseGameState::OpenNexpMap);
}

void ABaseGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABaseGameState, RoundTime);
	DOREPLIFETIME(ABaseGameState, PreStartRoundTimer);
	DOREPLIFETIME(ABaseGameState, RoundInProgress);
}

void ABaseGameState::OpenNexpMap(FName MapName)
{
	UKismetSystemLibrary::ExecuteConsoleCommand(this, FString("ServerTraver ") + MapName.ToString());
}

FTimespan ABaseGameState::GetRoundTime()
{
	return RoundTime;
}

FTimespan ABaseGameState::GetPreStartRoundTime()
{
	return PreStartRoundTimer;
}