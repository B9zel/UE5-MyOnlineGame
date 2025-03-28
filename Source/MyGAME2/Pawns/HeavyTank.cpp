
#include "HeavyTank.h"
#include <GameFramework/SpringArmComponent.h>
#include <Kismet/GameplayStatics.h>
#include <MyGAME2/bullet.h>
#include "../Game/BaseHUD.h"
#include <MyGAME2/BaseTank.h>
//#include <Kismet/KismetSystemLibrary.h>

AHeavyTank::AHeavyTank()
{
	Mesh->SetIsReplicated(true);
	Towermesh->SetIsReplicated(true);

	spring_arm->bUsePawnControlRotation = true;
	spring_arm->bInheritRoll = false;

	this->Max_HP = 300;

	Speed = 100.0f;
	
	Rotation_speed = 33.0f;

	Towerrotation_speed = 50.0f;

	TimeReload = 1.0;

	TimeDestroy = 4.0f;

	TimeUse_SuperPower = 0.0f;

	TimeReload_SuperPower = 4.0f;

	
	IsAim = false;

	isSuper_Power = false;

	StandartDamage = 20.0f;
	Damage = StandartDamage;

	SuperDamage = 50.0f;

	isReload = false;

	isReloadSuperPower = false;
}

void AHeavyTank::BeginPlay()
{
	ABaseTank::BeginPlay();

	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);

		
	}
}


void AHeavyTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("ForwardMove", this, &AHeavyTank::CallForwardMove);
	PlayerInputComponent->BindAxis("TurnMove", this, &AHeavyTank::CallRightMove);

	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &AHeavyTank::EnableAim);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &AHeavyTank::DisableAim);

	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AHeavyTank::Shoot_Server);
	PlayerInputComponent->BindAction("SuperPower", IE_Pressed, this, &AHeavyTank::EnableSuperPower_OnClient);
}

void AHeavyTank::Shoot_Server_Implementation()
{
	ABaseTank::Shoot_OnServer();

	if (isSuper_Power)
	{
		DisableSuperPower_OnServer();
		OnReloadSuperSkillWidget();

		isReloadSuperPower = true;
		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AHeavyTank::DisableReloadSuperPower, TimeReload_SuperPower, false);
	}
}

void AHeavyTank::EnableSuperPower_OnClient()
{
	EnableSuperPower_OnServer();
}

void AHeavyTank::EnableSuperPower_OnServer_Implementation()
{
	if (!isSuper_Power && !isReloadSuperPower && !isReload)
	{
		isSuper_Power = true;
		Damage = SuperDamage;
		ToggleActivateSuperSkillWidget(true);
	}
	else if(!isReloadSuperPower && !isReload)
	{
		DisableSuperPower_OnServer();
		ToggleActivateSuperSkillWidget(false);
	}
}


void AHeavyTank::DisableSuperPower_OnServer()
{
	isSuper_Power = false;
	Damage = StandartDamage;
}


void AHeavyTank::ToggleActivateSuperSkillWidget_Implementation(bool isActivate)
{
	if (HUD == nullptr)
	{
		HUD = GetController<APlayerController>() != nullptr ? GetController<APlayerController>()->GetHUD<ABaseHUD>() : nullptr;
	}

	if (isActivate)
	{
		HUD->ActivateSuperSkillWidget(true);
	}
	else
	{
		HUD->ActivateSuperSkillWidget(false);
	}
}

void AHeavyTank::OnReloadSuperSkillWidget_Implementation()
{
	if (HUD == nullptr)
	{
		HUD = GetController<APlayerController>() != nullptr ? GetController<APlayerController>()->GetHUD<ABaseHUD>() : nullptr;
	}
	
	HUD->ActivateSuperSkillWidget(false);
	HUD->ReloadSuperSkillWidget(TimeReload_SuperPower);
}

void AHeavyTank::DisableReloadSuperPower()
{
	isReloadSuperPower = false;
}

float AHeavyTank::GetSuperDamage()
{
	return SuperDamage;
}
