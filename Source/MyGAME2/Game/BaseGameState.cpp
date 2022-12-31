
#include "BaseGameState.h"
#include <Net/UnrealNetwork.h>
#include "Base_GameMode.h"
#include <Kismet/GameplayStatics.h>
#include <MyGAME2/PawnController.h>
#include <MyGAME2/Widgets/StatisticsMenu.h>
#include "../Enums/E_GameState.h"


ABaseGameState::ABaseGameState()
{
	this->PrimaryActorTick.bCanEverTick = true;
	this->PrimaryActorTick.TickInterval = 1.0f;

	SetReplicates(true);
	RoundInProgress = E_GameState::PreStart;
	
}

void ABaseGameState::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
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
	PreStartRoundTimer -= FTimespan::FromSeconds(1.0f);
	if (PreStartRoundTimer.GetTotalSeconds() <= 0 && RoundInProgress == E_GameState::PreStart)
	{
		Cast<ABase_GameMode>(UGameplayStatics::GetGameMode(this))->StartRound();
		RoundInProgress = E_GameState::Game;
		RoundStarted.Broadcast();
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
}

void ABaseGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABaseGameState, RoundTime);

	DOREPLIFETIME(ABaseGameState, PreStartRoundTimer);

	DOREPLIFETIME(ABaseGameState, RoundInProgress);
}

FTimespan ABaseGameState::GetRoundTime()
{
	return RoundTime;
}

FTimespan ABaseGameState::GetPreStartRoundTime()
{
	return PreStartRoundTimer;
}