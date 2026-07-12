
#include "Medium_Tank.h"
#include <GameFramework/SpringArmComponent.h>
#include <Engine/EngineTypes.h>
#include <Engine/CollisionProfile.h>
#include "../Game/BaseHUD.h"
#include "../Data/DataAssets/GhostTankConfigdataAsset.h"
#include "../HealthStat.h"




AMedium_Tank::AMedium_Tank()
{
	
	Mesh->SetIsReplicated(true);
	Towermesh->SetIsReplicated(true);

	spring_arm->bUsePawnControlRotation = true;
	spring_arm->bInheritRoll = false;

	Speed = 200.0f;

	Rotation_speed = 60.0f;

	Towerrotation_speed = 70.0f;

	TimeReload = 2.0f;

	TimeDestroy = 4.0f;

	TimeUse_SuperPower = 5.0f;

	TimeReload_SuperPower = 6.0f;

	Damage = 20.0f;

	isReload = false;

	IsAim = false;

	isSuper_Power = false;

}

void AMedium_Tank::BeginPlay()
{
	ABaseTank::BeginPlay();

	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}
	else
	{
		BeginCollision = Towermesh->GetCollisionEnabled();
		BaseMaterial = Mesh->GetMaterial(0);
		TowerMaterial = Towermesh->GetMaterial(0);
	}

}

void AMedium_Tank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("ForwardMove", this, &AMedium_Tank::ForwardInputMove);
	PlayerInputComponent->BindAxis("TurnMove", this, &AMedium_Tank::RotateInputMove);

	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &AMedium_Tank::EnableAim);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &AMedium_Tank::DisableAim);

	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AMedium_Tank::Shoot);
	PlayerInputComponent->BindAction("SuperPower", IE_Pressed, this, &AMedium_Tank::Enable_SuperPower_OnServer);
}

void AMedium_Tank::Enable_SuperPower_OnServer_Implementation()
{
	if (!isSuper_Power)
	{
		Enable_SuperPower_NetMulticast();
		EnableSuperPower_OnClient();

		isSuper_Power = true;

		FTimerHandle Handle;
		GetWorldTimerManager().SetTimer(Handle, this, &AMedium_Tank::Disable_SuperPower_OnServer, TimeUse_SuperPower, false);
	}
}

void AMedium_Tank::Enable_SuperPower_NetMulticast_Implementation()
{
	Towermesh->SetCollisionResponseToChannel(Collision, ECollisionResponse::ECR_Ignore);

	if (!HasAuthority())
	{
		Mesh->SetMaterial(0, BaseMaterial_NotCollision);
		Towermesh->SetMaterial(0, TowerMaterial_NotCollision);
	}
}

void AMedium_Tank::EnableSuperPower_OnClient_Implementation()
{
	GetController<APlayerController>()->GetHUD<ABaseHUD>()->ActivateSuperSkillWidget(TimeUse_SuperPower);
}

void AMedium_Tank::Disable_SuperPower_OnServer()
{
	Disable_SuperPower_NetMulticast();
	DisableSuperPower_OnClient();
	
	FTimerHandle Handle;
	GetWorldTimerManager().SetTimer(Handle, this, &AMedium_Tank::Disable_isSuperPower, TimeReload_SuperPower, false);
}

void AMedium_Tank::Disable_SuperPower_NetMulticast_Implementation()
{
	Towermesh->SetCollisionResponseToChannel(Collision, ECollisionResponse::ECR_Overlap);

	if (!HasAuthority())
	{
		Mesh->SetMaterial(0, BaseMaterial);
		Towermesh->SetMaterial(0, TowerMaterial);
	}
}

void AMedium_Tank::DisableSuperPower_OnClient_Implementation()
{
	GetController<APlayerController>()->GetHUD<ABaseHUD>()->ReloadSuperSkillWidget(TimeReload_SuperPower);
}

void AMedium_Tank::Disable_isSuperPower()
{
	isSuper_Power = false;
}

void AMedium_Tank::InitializeProperties()
{
	if (TankConfig)
	{
		Towerrotation_speed			= TankConfig->TowerRotationSpeed;
		TimeReload_SuperPower		= TankConfig->SkillTimeReload;
		TimeDestroy					= TankConfig->TimeDestroyAfterDeath;
		TimeUse_SuperPower			= TankConfig->SkillTimeUse;
		Rotation_speed				= TankConfig->RotationSpeed;
		TimeReload					= TankConfig->TimeReload;
		HP_Component->Max_HP = TankConfig->HealthPoints;
		Damage						= TankConfig->Damage;
		Speed						= TankConfig->Speed;

		BaseMaterial_NotCollision	= TankConfig->BaseMaterial_NotCollision;
		TowerMaterial_NotCollision	= TankConfig->TowerMaterial_NotCollision;
		Collision = TankConfig->Collision;
	}
}