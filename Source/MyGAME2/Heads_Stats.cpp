
#include "Heads_Stats.h"
#include <Net/UnrealNetwork.h>
#include <Kismet/GameplayStatics.h>
#include "BaseTank.h"
#include "Widget_HP.h"
#include "Game_Interface.h"
#include <MyGAME2/Game/Base_GameMode.h>
#include "PawnController.h"
#include <MyGAME2/Game/BaseHUD.h>


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
	/*ABaseHUD* HUD = Cast<APawnController>(GetOwner()->GetInstigatorController())->GetHUD<ABaseHUD>();
	if (owner->Main_Widget == nullptr && HUD->GetHUDWidget() != nullptr)
	{
		owner->Main_Widget = HUD->GetHUDWidget();
	}
	if (owner->Main_Widget != nullptr)
	{
		owner->Main_Widget->HeadsStats->UpdateData();
	}*/
	
}


void UHeads_Stats::Dead_OnOwnerClient()
{
	if (owner != nullptr && IsDead)
	{
		owner->DisableInput(Cast<APlayerController>(owner->GetController()));
		Dead_Server_Implementation();
	}
}

void UHeads_Stats::Dead_Server_Implementation()
{
	if (owner != nullptr)
	{
		owner->VisualDeadMulticast();
	}
}

void UHeads_Stats::InitailizrProperty_Implementation()
{
	Courrent_HP = Max_HP;
}
