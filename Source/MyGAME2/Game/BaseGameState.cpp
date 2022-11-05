
#include "BaseGameState.h"
#include <Net/UnrealNetwork.h>
#include "Base_GameMode.h"
#include <Kismet/GameplayStatics.h>
#include <MyGAME2/PawnController.h>
#include <MyGAME2/Widgets/StatisticsMenu.h>


ABaseGameState::ABaseGameState()
{
	SetReplicates(true);
	
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

			GameMode->RoundStart.AddDynamic(this, &ABaseGameState::OnRoundStarted);
		}
	}
}

void ABaseGameState::StartRoundTimer()
{
	GetWorldTimerManager().SetTimer(Timer, this, &ABaseGameState::TickRoundTime, 1.0f, true);
}

void ABaseGameState::TickRoundTime()
{
	RoundTime += FTimespan::FromSeconds(1.0f);

	if (GameMode->TimeLimit <= RoundTime)
	{
		//
		TimeEnded.Broadcast();
	}
	
}

void ABaseGameState::OnRoundEnded()
{
	GetWorldTimerManager().ClearTimer(Timer);
	RoundInProgress = false;
	RoundEnd_Multicast();
}

void ABaseGameState::RoundEnd_Multicast_Implementation()
{
	RoundEnded.Broadcast();
}

void ABaseGameState::OnRoundStarted()
{
	RoundInProgress = true;
	StartRoundTimer();
}

void ABaseGameState::OnRep_OnRoundInProgress()
{
	if (RoundInProgress)
	{
		RoundStarted.Broadcast();
	}
}

void ABaseGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABaseGameState, RoundTime);

	DOREPLIFETIME(ABaseGameState, RoundInProgress);
}
