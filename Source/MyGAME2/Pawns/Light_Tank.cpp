
#include "Light_Tank.h"
#include <GameFramework/SpringArmComponent.h>


ALight_Tank::ALight_Tank()
{
	Mesh->SetIsReplicated(true);
	Towermesh->SetIsReplicated(true);

	spring_arm->bUsePawnControlRotation = true;
	spring_arm->bInheritRoll = false;

	Speed = 300.0f;

	Rotation_speed = 90.0f;

	Towerrotation_speed = 90.0f;

	TimeReload = 1.5f;

	TimeDestroy = 4.0f;

	TimeUse_SuperPower = 5.0f;

	TimeReload_SuperPower = 6.0f;

	Damage = 30.0f;

	blockShoot = false;

	IsAim = false;

	isSuper_Power = false;

	Super_speed = 350.0f;

	Super_rotationSpeed = 20.0f;

	Super_TowerRotation_Speed = 15.0f;

	Max_HP = 200.0f;
}

void ALight_Tank::BeginPlay()
{
	ABaseTank::BeginPlay();

	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);

		GameMode = Get_GameMode(this);
	}
}

void ALight_Tank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("ForwardMove", this, &ALight_Tank::CallForwardMove);
	PlayerInputComponent->BindAxis("TurnMove", this, &ALight_Tank::CallRightMove);

	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &ALight_Tank::EnableAim);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &ALight_Tank::DisableAim);

	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &ALight_Tank::Shoot_OnServer);
	PlayerInputComponent->BindAction("SuperPower", IE_Pressed, this, &ALight_Tank::EnableSuperPower_OnServer);
}

void ALight_Tank::EnableSuperPower_OnServer_Implementation()
{
	if (!isSuper_Power)
	{
		isSuper_Power = true;

		Speed += Super_speed;
		Rotation_speed += Super_rotationSpeed;
		Towerrotation_speed += Super_TowerRotation_Speed;

		FTimerHandle Timer;
		GetWorldTimerManager().SetTimer(Timer, this, &ALight_Tank::DisableSuperPower_OnServer, TimeUse_SuperPower, false);
	}
}

void ALight_Tank::DisableSuperPower_OnServer()
{
	Speed -= Super_speed;
	Rotation_speed -= Super_rotationSpeed;
	Towerrotation_speed -= Super_TowerRotation_Speed;

	FTimerHandle Timer;
	GetWorldTimerManager().SetTimer(Timer, this, &ALight_Tank::Disable_isSuperPower, TimeReload_SuperPower, false);
}

void ALight_Tank::Disable_isSuperPower()
{
	isSuper_Power = false;
}
