
#include "Base_GameMode.h"
#include <MyGAME2/Enums/E_Team.h>
#include <MyGAME2/BaseTank.h>
#include <MyGAME2/PawnController.h>
#include <Engine/World.h>
#include <MyGAME2/Pawns/HeavyTank.h>
#include <MyGAME2/Game_Spectator.h>
#include <MyGAME2/Game/BaseHUD.h>
#include "BaseGameState.h"
#include <Kismet/GameplayStatics.h>
#include "PlayerStatistic.h"
#include <MyGAME2/Game_Interface.h>
#include <MyGAME2/Game/PlayerStatistic.h>



ABase_GameMode::ABase_GameMode()
{
	PrimaryActorTick.bCanEverTick = false;

	AutoRespawn = true;
}

void ABase_GameMode::BeginPlay()
{
	Super::BeginPlay();

}

void ABase_GameMode::Pawn_Dead_Implementation(APlayerController* DeadPlayer, APlayerController* DeadInstigator)
{
	UpdateDeathPoints(DeadPlayer, DeadInstigator);
	SpawnSpectator(DeadPlayer, DeadInstigator);
	Cast<APlayerStatistic>(DeadPlayer->PlayerState)->OnwerPawnDead(Cast<ABaseTank>(DeadInstigator->GetPawn()));
	
	if (AutoRespawn)
	{
		Cast<APawnController>(DeadPlayer)->TimerRespawn(5.0f);
	}
}

void ABase_GameMode::SpawnSpectator(class APlayerController* Player, class APlayerController* DeadInstigator)
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = Player;

	//Spawn Spectator
	AGame_Spectator* SpawnActor = GetWorld()->SpawnActor<AGame_Spectator>(Spectator_Class, FTransform(Player->GetPawn()->GetActorLocation() + FVector(0, 0, 50)), SpawnParameters);
	if (DeadInstigator != nullptr)
	{
		SpawnActor->FollowPawn = Cast<ABaseTank>(DeadInstigator->GetPawn());
	}
	Player->Possess(SpawnActor);
}

void ABase_GameMode::StartRound_Implementation()
{
	ABaseGameState* Game_State = Cast<ABaseGameState>(UGameplayStatics::GetGameState(this));
	class APawnController* Controller;

	for (auto& el : Game_State->PlayerArray)
	{
		Controller = Cast<APawnController>(el.Get()->GetOwner());
		Spawn_Player(Controller, Controller->Spawn_Pawn);
	}
	RoundStart.Broadcast();
}

void ABase_GameMode::UpdateDeathPoints_Implementation(APlayerController* DeadPlayer, APlayerController* DeathInstigatorPlayer)
{
	Cast<APlayerStatistic>(DeadPlayer->PlayerState)->AddDeath();
	Cast<APlayerStatistic>(DeathInstigatorPlayer->PlayerState)->AddKill();
}

void ABase_GameMode::StopRound()
{
	class AGameStateBase* Game_State = UGameplayStatics::GetGameState(this);
	class APawnController* PlayerController;

	for (auto& el : Game_State->PlayerArray)
	{	
		PlayerController = Cast<APawnController>(el->GetOwner());
		SpawnSpectator(PlayerController, nullptr);
	}

	TArray<AActor*,FDefaultAllocator> ArrBaseTank;
	UGameplayStatics::GetAllActorsOfClass(this, ABaseTank::StaticClass(), ArrBaseTank);
	ArrBaseTank.RemoveAll([](class AActor* actor)
	{
		return actor->Destroy();
	});

	RoundEnded.Broadcast();
}

void ABase_GameMode::RechedTimeLimit()
{
	if (LimiyByTimer)
	{
		StopRound();
	}
}

bool ABase_GameMode::ShouldDamagePlayer_Implementation(APlayerController* Player, APlayerController* InstigatorPLayer)
{
	return true;
}
