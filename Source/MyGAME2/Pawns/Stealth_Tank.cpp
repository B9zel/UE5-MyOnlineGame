
#include "Stealth_Tank.h"
#include <GameFramework/SpringArmComponent.h>
#include <MyGAME2/HealthStat.h>
#include <Net/UnrealNetwork.h>
#include "../Game/BaseHUD.h"
#include "../Data/DataAssets/InvisibleTankConfigdataAsset.h"
#include "../HealthStat.h"



AStealth_Tank::AStealth_Tank()
{
	Mesh->SetIsReplicated(true);
	Towermesh->SetIsReplicated(true);

	OnTakeAnyDamage.AddDynamic(this, &AStealth_Tank::Take_Damage);

	spring_arm->bUsePawnControlRotation = true;
	spring_arm->bInheritRoll = false;

	Speed = 250.0f;

	Rotation_speed = 60.0f;

	Towerrotation_speed = 80.0f;

	TimeReload = 2.0;

	TimeDestroy = 4.0f;

	TimeUse_SuperPower = 5.0f;

	TimeReload_SuperPower = 6.0f;

	Damage = 50.0f;

	isReload = false;

	IsAim = false;

	isSuper_Power = false;

	isUseSuper_Power = true;
}

void AStealth_Tank::BeginPlay()
{
	ABaseTank::BeginPlay();

	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}
}

void AStealth_Tank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("ForwardMove", this, &AStealth_Tank::ForwardInputMove);
	PlayerInputComponent->BindAxis("TurnMove", this, &AStealth_Tank::RotateInputMove);

	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &AStealth_Tank::EnableAim);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &AStealth_Tank::DisableAim);

	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AStealth_Tank::Shoot);
	PlayerInputComponent->BindAction("SuperPower", IE_Pressed, this, &AStealth_Tank::EnableSuperPower_OnClient);
}

void AStealth_Tank::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AStealth_Tank, isUseSuper_Power);

}

void AStealth_Tank::Take_Damage(AActor* DamagedActor, float damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (HP_Component->IsDead && isSuper_Power)
	{
		GetWorldTimerManager().ClearTimer(TimerKey);
		DisableSuperPower_Multicast();
	}
	else if (isSuper_Power)
	{
		DisableSuperPower_Multicast();
		isUseSuper_Power = true;

		FTimerHandle Handle;
		GetWorldTimerManager().SetTimer(Handle, this, &AStealth_Tank::EnableSuperPower_OnClient, 0.1f, false);
	}
}

void AStealth_Tank::EnableSuperPower_OnClient_Implementation()
{
	if (!isSuper_Power && isUseSuper_Power)
	{
		if (Material_InvisibleBase != nullptr && Material_InvisibleTower != nullptr && Material_Base != nullptr)
		{
			Mesh->SetMaterial(0, Material_InvisibleBase);
			Towermesh->SetMaterial(0, Material_InvisibleTower);
		}
		isSuper_Power = true;

		GetController<APlayerController>()->GetHUD<ABaseHUD>()->ActivateSuperSkillWidget(TimeUse_SuperPower);
		EnableSuperPower_OnServer();
	}
}


void AStealth_Tank::EnableSuperPower_OnServer_Implementation()
{
	EnableSuperPower_Multicast();
	
	if (!GetWorldTimerManager().IsTimerActive(TimerKey))
	{
		GetWorldTimerManager().SetTimer(TimerKey, this, &AStealth_Tank::StartReload_SuperPower_OnServer, TimeUse_SuperPower, false);
		isSuper_Power = true;
	}
	isUseSuper_Power = false;
}

void AStealth_Tank::EnableSuperPower_Multicast_Implementation()
{
	if (!HasAuthority() && !isSuper_Power)
	{
		Mesh->SetVisibility(false);
		Towermesh->SetVisibility(false);
	}
}

void AStealth_Tank::DisableSuperPower_OnClient()
{
	APlayerController* controller = GetController<APlayerController>();
	if (controller != nullptr)
	{
		controller->GetHUD<ABaseHUD>()->ReloadSuperSkillWidget(TimeReload_SuperPower);
	}
	if (Material_Base != nullptr && Material_BaseTower != nullptr)
	{
		Mesh->SetMaterial(0, Material_Base);
		Towermesh->SetMaterial(0, Material_BaseTower);
	}
	isSuper_Power = false;
}


void AStealth_Tank::DisableSuperPower_Multicast_Implementation()
{
	if (!HasAuthority())
	{
		if (isSuper_Power)
			DisableSuperPower_OnClient();
		else
		{
			Mesh->SetVisibility(true);
			Towermesh->SetVisibility(true);
		}
	}
}

void AStealth_Tank::StartReload_SuperPower_OnServer()
{
	DisableSuperPower_Multicast();
	isSuper_Power = false;

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AStealth_Tank::EnableUse_SuperPower, TimeReload_SuperPower, false);
}

inline void AStealth_Tank::EnableUse_SuperPower()
{
	isUseSuper_Power = true;
}


void AStealth_Tank::InitializeProperties()
{
	if (TankConfig)
	{
		Towerrotation_speed		= TankConfig->TowerRotationSpeed;
		TimeReload_SuperPower	= TankConfig->SkillTimeReload;
		TimeDestroy				= TankConfig->TimeDestroyAfterDeath;
		TimeUse_SuperPower		= TankConfig->SkillTimeUse;
		Rotation_speed			= TankConfig->RotationSpeed;
		TimeReload				= TankConfig->TimeReload;
		HP_Component->Max_HP	= TankConfig->HealthPoints;
		Damage					= TankConfig->Damage;
		Speed					= TankConfig->Speed;

		Material_InvisibleBase	= TankConfig->Material_InvisibleBase;
		Material_InvisibleTower = TankConfig->Material_InvisibleTower;
	}
	Material_Base = Mesh->GetMaterial(0);
	Material_BaseTower = Mesh->GetMaterial(0);
}