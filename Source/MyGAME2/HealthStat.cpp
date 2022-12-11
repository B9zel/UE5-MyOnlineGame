// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthStat.h"
#include <Net/UnrealNetwork.h>
#include <Kismet/GameplayStatics.h>
#include "BaseTank.h"
#include "Widget_HP.h"
#include "Game_Interface.h"
#include <MyGAME2/Game/Base_GameMode.h>
#include "PawnController.h"
#include <MyGAME2/Game/BaseHUD.h>
// Sets default values for this component's properties
UHealthStat::UHealthStat()
{
	PrimaryComponentTick.bCanEverTick = false;

	SetIsReplicated(true);
	
	IsDead = false;

	Impulse = 50000.0f;
}


// Called when the game starts
void UHealthStat::BeginPlay()
{
	Super::BeginPlay();

	owner = Cast<ABaseTank>(GetOwner());
	if (owner != nullptr)
	{
		owner->OnTakeAnyDamage.AddDynamic(this, &UHealthStat::OnPlayerTakeAnyDamage);
	}
	
}



void UHealthStat::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UHealthStat, Courrent_HP, COND_OwnerOnly);

	DOREPLIFETIME_CONDITION(UHealthStat, Max_HP, COND_OwnerOnly);

	DOREPLIFETIME(UHealthStat, IsDead);
}

void UHealthStat::OnPlayerTakeAnyDamage(AActor* DamagedActor, float damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (owner->GameMode->ShouldDamagePlayer(Cast<APlayerController>(owner->GetController()), Cast<APlayerController>(InstigatedBy)))
	{
		Courrent_HP -= FMath::Clamp(damage, 0.0f, Max_HP);

		if (Courrent_HP <= 0.0f && !IsDead)
		{
			owner->GameMode->Pawn_Dead(Cast<APlayerController>(owner->GetController()), Cast<APlayerController>(InstigatedBy));

			FTimerHandle handle;
			GetWorld()->GetTimerManager().SetTimer(handle, Cast<ABaseTank>(GetOwner()), &ABaseTank::Destroy, owner->TimeDestroy, false);
			IsDead = true;
		}
	}
}

void UHealthStat::OnRep_UpdateWidget()
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

void UHealthStat::Dead_OnOwnerClient()
{
	if (owner != nullptr && IsDead)
	{
		owner->DisableInput(Cast<APlayerController>(owner->GetController()));
		Dead_Server_Implementation();
	}
}

void UHealthStat::Dead_Server_Implementation()
{
	if (owner != nullptr)
	{
		owner->VisualDeadMulticast();
	}
}

void UHealthStat::InitailizrProperty_Implementation()
{
	Courrent_HP = Max_HP;
}
