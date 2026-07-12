
#include "Light_Tank.h"
#include <GameFramework/SpringArmComponent.h>
#include "../Game/BaseHUD.h"
#include "../Data/DataAssets/LightTankConfigdataAsset.h"

#include "../HealthStat.h"



ALight_Tank::ALight_Tank()
{
	Mesh->SetIsReplicated(true);
	Towermesh->SetIsReplicated(true);

	spring_arm->bUsePawnControlRotation = true;
	spring_arm->bInheritRoll = false;

	Speed = 300.0f;

	Rotation_speed = 90.0f;

	Towerrotation_speed = 60.0f;

	TimeReload = 1.5f;

	TimeDestroy = 4.0f;

	TimeUse_SuperPower = 5.0f;

	TimeReload_SuperPower = 6.0f;

	Damage = 30.0f;

	isReload = false;

	IsAim = false;

	isSuper_Power = false;

	Super_speed = 350.0f;

	Super_rotationSpeed = 20.0f;

	Super_TowerRotation_Speed = 15.0f;

}

void ALight_Tank::BeginPlay()
{
	ABaseTank::BeginPlay();

	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);

	}
}

void ALight_Tank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("ForwardMove", this, &ALight_Tank::ForwardInputMove);
	PlayerInputComponent->BindAxis("TurnMove", this, &ALight_Tank::RotateInputMove);

	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &ALight_Tank::EnableAim);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &ALight_Tank::DisableAim);

	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &ALight_Tank::Shoot);
	PlayerInputComponent->BindAction("SuperPower", IE_Pressed, this, &ALight_Tank::EnableSuperPower_OnServer);
}

void ALight_Tank::InitializeProperties()
{
	if (TankConfig)
	{
		Towerrotation_speed			= TankConfig->TowerRotationSpeed;
		TimeReload_SuperPower		= TankConfig->SkillTimeReload;
		TimeDestroy					= TankConfig->TimeDestroyAfterDeath;
		TimeUse_SuperPower			= TankConfig->SkillTimeUse;
		Rotation_speed				= TankConfig->RotationSpeed;
		TimeReload					= TankConfig->TimeReload;
		HP_Component->Max_HP		= TankConfig->HealthPoints;
		Damage						= TankConfig->Damage;
		Speed						= TankConfig->Speed;

		Super_rotationSpeed			= TankConfig->SkillRotationSpeed;
		Super_TowerRotation_Speed	= TankConfig->SkillTowerRotationSpeed;
		Super_speed					= TankConfig->SkillSpeed;
	}
}

void ALight_Tank::EnableSuperPower_OnClient_Implementation()
{
	GetController<APlayerController>()->GetHUD<ABaseHUD>()->ActivateSuperSkillWidget(TimeUse_SuperPower);
}

void ALight_Tank::EnableSuperPower_OnServer_Implementation()
{
	if (!isSuper_Power)
	{
		isSuper_Power = true;

		DefaultSpeed = Speed;
		DefaultRotationSpeed = Rotation_speed;
		DefaultTowerRotationSpeed = Towerrotation_speed;

		Speed = Super_speed;
		Rotation_speed = Super_rotationSpeed;
		Towerrotation_speed = Super_TowerRotation_Speed;

		EnableSuperPower_OnClient();
		FTimerHandle Timer;
		GetWorldTimerManager().SetTimer(Timer, this, &ALight_Tank::DisableSuperPower_OnServer, TimeUse_SuperPower, false);
	}
}

void ALight_Tank::DisableSuperPower_OnServer()
{
	Speed = DefaultSpeed;
	Rotation_speed = DefaultRotationSpeed;
	Towerrotation_speed = DefaultTowerRotationSpeed;

	DisableSuperPower_OnClient();
	FTimerHandle Timer;
	GetWorldTimerManager().SetTimer(Timer, this, &ALight_Tank::Disable_isSuperPower, TimeReload_SuperPower, false);
}

void ALight_Tank::DisableSuperPower_OnClient_Implementation()
{
	GetController<APlayerController>()->GetHUD<ABaseHUD>()->ReloadSuperSkillWidget(TimeReload_SuperPower);
}

void ALight_Tank::Disable_isSuperPower()
{
	isSuper_Power = false;
}
