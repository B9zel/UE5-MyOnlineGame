
#include "Base_GameMode.h"
#include <MyGAME2/BaseTank.h>
#include <MyGAME2/PawnController.h>
#include <Engine/World.h>
#include <MyGAME2/Pawns/HeavyTank.h>
#include <MyGAME2/Game_Spectator.h>
#include <GameFramework/SpringArmComponent.h>
//#include <GameFramework/PlayerState.h>
#include "BaseGameState.h"
#include <Kismet/GameplayStatics.h>
#include "PlayerStatistic.h"
#include <MyGAME2/Game_Interface.h>

ABase_GameMode::ABase_GameMode()
{
	AutoRespawn = true;

}

void ABase_GameMode::BeginPlay()
{
	Super::BeginPlay();

	ABaseGameState* Game_State = Cast<ABaseGameState>(UGameplayStatics::GetGameState(this));
	if (GameState == UGameplayStatics::GetGameState(this))
	{
		Game_State->TimeEnded.AddDynamic(this,&ABase_GameMode::RechedTimeLimit);
	}
	
	FTimerHandle Handle;
	GetWorldTimerManager().SetTimer(Handle, this, &ABase_GameMode::StartRound, 4.0f, false);
}

void ABase_GameMode::Pawn_Dead_Implementation(ABaseTank* DeadPawn, APlayerController* DeadInstigator)
{
	UpdateDeathPoints(Cast<APlayerController>(DeadPawn->GetController()), DeadInstigator);
	if (AutoRespawn)
	{
		Cast<APawnController>(DeadPawn->Controller)->TimerRespawn(5.0f);
	}

}

AGame_Spectator* ABase_GameMode::Spawn_Spectator(class APlayerController* Player, class APlayerController* DeadInstigator)
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = Player;
	
	ABaseTank* Pawn_of_DeadInstigator = Cast<ABaseTank>(DeadInstigator->GetPawn());

	//Spawn Spectator
	AGame_Spectator* SpawnActor = GetWorld()->SpawnActor<AGame_Spectator>(Spectator_Class, FTransform(Pawn_of_DeadInstigator->spring_arm->GetComponentLocation()), SpawnParameters); // - FVector(0.0f, 0.0f, 500.0f))

	SpawnActor->FollowPawn = Pawn_of_DeadInstigator;

	Player->GetPawn()->Destroy();
	Player->Possess(SpawnActor);
	
	return SpawnActor;
}

void ABase_GameMode::StartRound()
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

void ABase_GameMode::UpdateDeathPoints(APlayerController* DeadPlayer, APlayerController* DeathInstigatorPlayer)
{
	Cast<APlayerStatistic>(DeadPlayer->PlayerState)->AddDeath();
	Cast<APlayerStatistic>(DeathInstigatorPlayer->PlayerState)->AddKill();
}

void ABase_GameMode::StopRound()
{
	class AGameStateBase* Game_State = UGameplayStatics::GetGameState(this);
	class APawnController* PlayerController;

	AutoRespawn = false;
	for (auto& el : Game_State->PlayerArray)
	{	
		PlayerController = Cast<APawnController>(el->GetOwner());
		
		
		PlayerController->GetPawn()->Destroy();
	}
	RoundEnded.Broadcast();
	
}

void ABase_GameMode::StopRoundOnClient_Implementation(APlayerController* PlayerController)
{
	if (!HasAuthority())
	{
		DisableInput(PlayerController);
		APawnController* Controller = Cast<APawnController>(PlayerController);
		if (Controller->Game_Interface != nullptr)
		{
			Controller->Game_Interface->RemoveFromParent();
		}
	}
}

void ABase_GameMode::RechedTimeLimit()
{
	if (LimiyByTimer)
	{
		StopRound();
	}
}
