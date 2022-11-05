
#include "HeavyTank.h"
#include <GameFramework/SpringArmComponent.h>
#include <Kismet/GameplayStatics.h>
#include <MyGAME2/bullet.h>
//#include <MyGAME2/Heads_Stats.h>
#include <MyGAME2/BaseTank.h>
//#include <Kismet/KismetSystemLibrary.h>

AHeavyTank::AHeavyTank()
{
	Mesh->SetIsReplicated(true);
	Towermesh->SetIsReplicated(true);

	spring_arm->bUsePawnControlRotation = true;
	spring_arm->bInheritRoll = false;

	Speed = 100.0f;
	
	Rotation_speed = 33.0f;

	Towerrotation_speed = 50.0f;

	TimeReload = 3.0;

	Time_SpawnSpectator = 4.0f;

	TimeUse_SuperPower = 0.0f;

	TimeReload_SuperPower = 4.0f;

	Damage = 20.0f;

	blockShoot = false;

	IsAim = false;

	isSuper_Power = false;

	SuperDamage_Multiply = 2.0f;
}

void AHeavyTank::BeginPlay()
{
	ABaseTank::BeginPlay();

	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);

		GameMode = Get_GameMode(this);
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
		isSuper_Power = false;
		DisableSuperPower_OnServer_Implementation();

		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AHeavyTank::Disable_isSuperPower, TimeReload_SuperPower, false);
	}
}

void AHeavyTank::EnableSuperPower_OnClient()
{
	EnableSuperPower_OnServer();
}

void AHeavyTank::EnableSuperPower_OnServer_Implementation()
{
	if (isSuper_Power)
	{
		isSuper_Power = true;
		Damage *= SuperDamage_Multiply;
	}
}

void AHeavyTank::DisableSuperPower_OnServer_Implementation()
{
	Damage /= SuperDamage_Multiply;
}

void AHeavyTank::Disable_isSuperPower()
{
	isSuper_Power = false;
}