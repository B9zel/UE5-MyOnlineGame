
#include "BaseTank.h"
#include <Components/StaticMeshComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include <Components/SceneComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include <Kismet/GameplayStatics.h>
#include <Components/AudioComponent.h>
#include <NiagaraFunctionLibrary.h>
#include <NiagaraSystem.h>
#include <NiagaraComponent.h>
#include <Net/UnrealNetwork.h>
#include "HealthStat.h"
#include "bullet.h"
#include "Widget_Reload.h"
#include "Game_Interface.h"
//#include <GameFramework/GameModeBase.h>
#include "Game/Base_GameMode.h"
#include "PawnController.h"
#include "Game/PlayerStatistic.h"
#include "Widgets/InGame/W_SuperPower.h"
#include "Game/BaseHUD.h"



ABaseTank::ABaseTank()
{
	
	PrimaryActorTick.bCanEverTick = true;
	

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	Towermesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Towermesh"));
	Towermesh->SetupAttachment(Mesh);
	
	spring_arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("springarm"));
	spring_arm->SetupAttachment(Mesh);

	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("camera"));
	camera->SetupAttachment(spring_arm);
	camera->FieldOfView = 97.0f;

	bscene = CreateDefaultSubobject<USceneComponent>(TEXT("BScene"));
	bscene->SetupAttachment(Towermesh);

	AudioShoot = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Shoot"));
	AudioShoot->SetupAttachment(bscene);
	AudioShoot->SetAutoActivate(false);
	
		//N_ExplosionShoot->SetupAttachment(Towermesh);
	//N_ExplosionShoot->SetAutoActivate(false);
	

	SecondCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Second Camera"));
	SecondCamera->SetupAttachment(Towermesh);
	SecondCamera->bAutoActivate = false;
	SecondCamera->SetVisibility(false);

	HP_Component = CreateDefaultSubobject<UHealthStat>(TEXT("HealthStat"));

}

void ABaseTank::PossessedBy(AController* controller)
{
	Super::PossessedBy(controller);

	controller->ClientSetRotation(Towermesh->GetComponentRotation());
}

void ABaseTank::BeginPlay()
{
	Super::BeginPlay();

	HP_Component->Max_HP = this->Max_HP;
	
	if (!HasAuthority())
	{
		N_ExplosionShoot = UNiagaraFunctionLibrary::SpawnSystemAttached(struction.ExplosionShoot, bscene, TEXT("Niagara"), FVector(0.f), FRotator(0.f), EAttachLocation::Type::KeepRelativeOffset, false,false);
		HUD = GetController<APlayerController>() != nullptr ? GetController<APlayerController>()->GetHUD<ABaseHUD>() : nullptr;
		if (HUD != nullptr)
		{
			HUD->superskillWidgetClass = struction.superSkillWidgetClass;
			HUD->CreateAimWidget();
		}
	}
	else
	{
		gameMode = Cast<ABase_GameMode>(UGameplayStatics::GetGameMode(this));
	}
	D_SpawnTankPawn.Broadcast(this);
}

void ABaseTank::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (EEndPlayReason::Type::Destroyed == EndPlayReason)
	{
		if (N_ExplosionShoot != nullptr)
			N_ExplosionShoot->DestroyComponent();
	}
	if (HUD != nullptr)
	{
		HUD->RemoveAimWidget();
	}
}


// Called every frame
void ABaseTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!HP_Component->IsDead && !HasAuthority())
	{
		ClientRotateTower();
	}
}

void ABaseTank::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABaseTank, isReload);
}

void ABaseTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABaseTank::CallForwardMove_Implementation(float axis)
{
	ForwardMove_Implementation(axis);
}

void ABaseTank::ForwardMove_Implementation(float Axis)
{
	if (Controller != nullptr && Axis != 0.0f && HasAuthority())
	{
		FVector diraction = GetActorLocation() + (GetActorForwardVector() * Axis) * (Speed * GetWorld()->GetDeltaSeconds());
	
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *diracthion.ToString());
		TeleportTo(diraction, GetActorRotation());
	}
}

void ABaseTank::CallRightMove_Implementation(float axis)
{
	RightMove_Implementation(axis);
}

void ABaseTank::RightMove_Implementation(float Axis)
{
	if (Controller != nullptr && Axis != 0.0f && HasAuthority())
	{
		FRotator diraction = GetActorRotation();
		diraction.Yaw += Axis * Rotation_speed * GetWorld()->GetDeltaSeconds();

		TeleportTo(GetActorLocation(), diraction);
	}
}


void ABaseTank::ClientRotateTower()
{	
	if (IsLocallyControlled())
	{
		target = GetControlRotation().Yaw - Mesh->GetComponentRotation().Yaw;
		if (target > 180)
			target -= 360;
		if (target != Towermesh->GetRelativeRotation().Yaw)
			RotateTower_OnServer(target);
	}
}

void ABaseTank::RotateTower_OnServer_Implementation(float Target)
{	
	Towermesh->SetRelativeRotation(FRotator(0.0f, FMath::Clamp(InterpTo(Towermesh->GetRelativeRotation().Yaw, Target, GetWorld()->GetDeltaSeconds(), Towerrotation_speed), -120.0f, 120.0f), 0.0f));
}

void ABaseTank::EnableAim()
{
	if (this->HUD == nullptr)
	{
		HUD = GetController<APlayerController>() != nullptr ? GetController<APlayerController>()->GetHUD<ABaseHUD>() : nullptr;
	}
	
	
	if (HUD != nullptr)
	{
		IsAim = true;
		camera->Deactivate();
		SecondCamera->Activate();

		HUD->ToggleAim(true);
	}
}

void ABaseTank::DisableAim()
{
	if (this->HUD == nullptr)
	{
		HUD = GetController<APlayerController>() != nullptr ? GetController<APlayerController>()->GetHUD<ABaseHUD>() : nullptr;
	}

	IsAim = false;
	SecondCamera->Deactivate();
	camera->Activate();

	if (HUD != nullptr)
	{
		HUD->ToggleAim(false);
	}
}

void ABaseTank::Shoot_OnServer_Implementation()
{
	if (struction.objectBullet != nullptr && !isReload)
	{
		isReload = true;
		FActorSpawnParameters spawnParametars;
		spawnParametars.Owner = this;
		
		Abullet* Ref_Bullet = GetWorld()->SpawnActor<Abullet>(struction.objectBullet, FTransform(bscene->GetComponentRotation(), bscene->GetComponentLocation(), FVector(1.0f, 1.0f, 1.0f)), spawnParametars);
		if (Ref_Bullet != nullptr)
		{
			Shoot_Multicast();
		}
		FTimerHandle handle;
		GetWorldTimerManager().SetTimer(handle, this, &ABaseTank::RecharchShoot, TimeReload + 0.1f, false);
	}
}

void ABaseTank::Shoot_Multicast_Implementation()
{	
	if (!HasAuthority())
	{
		if (!IsAim)
		{
			//Spawn Explosion 
			N_ExplosionShoot->ActivateSystem(true);
		}

		//Start Widget Timer
		D_ReloadStart.Broadcast(TimeReload,0.1f,0.1f);
		
		//Spawn Sound
		AudioShoot->SetActive(true, true);
	}
}

void ABaseTank::RecharchShoot()
{
	isReload = false;
	Widget_ReloadShoot();
}

void ABaseTank::Widget_ReloadShoot_Implementation()
{
	/*if (Main_Widget != nullptr)
	{
		if (Main_Widget->ReloadStats != nullptr)
			Main_Widget->ReloadStats->FinishTimer();
	}*/
	//AudioShoot->Deactivate();
	
	D_ReloadEnd.Broadcast();
}

void ABaseTank::VisualDeadMulticast_Implementation()
{
	if (!HasAuthority())
	{
		Mesh->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
		Towermesh->SetCollisionEnabled(ECollisionEnabled::Type::PhysicsOnly);
		Towermesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);
		
		//Spaen Niagara
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), struction.ExplosionDeath, Towermesh->GetComponentLocation(), Towermesh->GetComponentRotation(), FVector(1));
		
		Towermesh->SetSimulatePhysics(true);
		Towermesh->AddImpulse(FVector(FMath::FRandRange(HP_Component->Impulse * -1, HP_Component->Impulse), FMath::FRandRange(HP_Component->Impulse * -1, HP_Component->Impulse), HP_Component->Impulse));
	}
}

void ABaseTank::Destroy()
{
	AActor::Destroy();
}

ABase_GameMode* ABaseTank::GetGameMode()
{
	return this->gameMode;
}


void ABaseTank::ActivateOurTeamMaterial()
{
	Mesh->SetOverlayMaterial(struction.M_OutTeam);
	Towermesh->SetOverlayMaterial(struction.M_OutTeam);
}

float ABaseTank::GetSpeed()
{
	return Speed;
}

float ABaseTank::GetRotationSpeed()
{
	return Rotation_speed;
}

float ABaseTank::GetTowerRotationSpeed()
{
	return Towerrotation_speed;
}

float ABaseTank::GetDamage()
{
	return Damage;
}

float ABaseTank::GetHP()
{
	return Max_HP;
}

float ABaseTank::GetTimeReload()
{
	return TimeReload;
}

float ABaseTank::GetTimeReloadSuperPower()
{
	return TimeReload_SuperPower;
}

float ABaseTank::GetTimeUseSuperPower()
{
	return TimeUse_SuperPower;
}

float ABaseTank::GetTimeDestroy()
{
	return TimeDestroy;
}


float ABaseTank::InterpTo(float Current, float Target, float DeltaTime, float speed)
{
	if (Current == Target)
		return Current;
	
	float DeltaSpeed = speed * DeltaTime;
	
	if (Current > Target - 4.f  && Current < Target + 4.f)
	{
		return Current + FMath::Clamp<float>(DeltaSpeed, 0, 1) * (Target - Current);
	}
	else
	{
	//UE_LOG(LogTemp, Warning, TEXT("Target: %f"), Target);
		if (Current < Target)
		{
			return Current + DeltaSpeed;
		}	
		else 
		{
			return Current - DeltaSpeed;
		}
	}
}

//TSubclassOf<UW_SuperPower> ABaseTank::GetSuperSkillWidget()
//{
//	//Cast<APlayerController>(GetController())->GetHUD<ABaseHUD>()->superskillWidgetClass =
//	return struction.superSkillWidgetClass;
//}
