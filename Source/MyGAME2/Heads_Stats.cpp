
#include "Heads_Stats.h"
#include <Net/UnrealNetwork.h>
#include <Kismet/GameplayStatics.h>
#include "BaseTank.h"
#include "Widget_HP.h"
#include "Game_Interface.h"
#include <MyGAME2/Game/Base_GameMode.h>
#include "PawnController.h"


// Sets default values for this component's properties
UHeads_Stats::UHeads_Stats()
{
	PrimaryComponentTick.bCanEverTick = false;
	
	SetIsReplicated(true);
	IsDead = false;
	
	Impulse = 50000.0f;

}



// Called when the game starts
void UHeads_Stats::BeginPlay()
{
	Super::BeginPlay();

	owner = Cast<ABaseTank>(GetOwner());
}


// Called every frame
void UHeads_Stats::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	//UE_LOG(LogTemp, Warning, TEXT("Output %d"), StopUpdate);
	//UE_LOG(LogTemp, Warning, TEXT("Output %f"), Courrent_HP);
}

void UHeads_Stats::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION(UHeads_Stats, Courrent_HP,COND_OwnerOnly);

	DOREPLIFETIME_CONDITION(UHeads_Stats, Max_HP, COND_OwnerOnly);

	DOREPLIFETIME(UHeads_Stats, IsDead);
}

void UHeads_Stats::OnRep_UpdateWidget()
{
	if (owner != nullptr)
	{
		if (owner->Main_Widget != nullptr)
		{
			owner->Main_Widget->Widget_HP->UpdateData();
		}
	}
}


void UHeads_Stats::Dead_OnOwnerClient()
{
	if (owner != nullptr && IsDead)
	{
		/*if (owner->Main_Widget != nullptr)
		{
			owner->Main_Widget->SetVisibility(ESlateVisibility::Collapsed);
		}*/
		owner->DisableInput(Cast<APlayerController>(owner->GetController()));
		Dead_Server();
	}
}

void UHeads_Stats::Dead_Server_Implementation()
{
	if (owner != nullptr)
	{
		Cast<APawnController>(owner->GetController())->isActivateWidget = false;
		owner->VisualDeadMulticast();
	}
}

void UHeads_Stats::InitailizrProperty_Implementation()
{
	Courrent_HP = Max_HP;
}

void UHeads_Stats::CallSpawnSpectator()
{
	if (owner != nullptr)
	{
		owner->GameMode->Spawn_Spectator(Cast<APlayerController>(owner->GetController()), Cast<APlayerController>(EnamyController));
	}
}
