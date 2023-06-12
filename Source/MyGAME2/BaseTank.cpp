
#include "BaseTank.h"
#include <Components/StaticMeshComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include <Components/SceneComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include <Kismet/GameplayStatics.h>
#include <GameFramework/Controller.h>
#include <MyGAME2/PawnController.h>
#include <Net/UnrealNetwork.h>
#include <MyGAME2/HealthStat.h>
#include "bullet.h"
#include "Widget_Reload.h"
#include "Game_Interface.h"
#include <MyGAME2/Game/Base_GameMode.h>
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

	SecondCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Second Camera"));
	SecondCamera->SetupAttachment(Towermesh);
	SecondCamera->bAutoActivate = false;
	SecondCamera->SetVisibility(false);

	HP_Component = CreateDefaultSubobject<UHealthStat>(TEXT("HealthStat"));

	projectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	
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
		ABaseHUD* HUD = GetController<APlayerController>() != nullptr ? GetController<APlayerController>()->GetHUD<ABaseHUD>() : nullptr;
		if (HUD != nullptr)
		{
			HUD->superskillWidgetClass = struction.superSkillWidgetClass;
		}
	}
	
}


// Called every frame
void ABaseTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
//	UE_LOG(LogTemp, Warning, TEXT("Releativ %f"), Towermesh->GetRelativeRotation().Yaw);
//	UE_LOG(LogTemp, Warning, TEXT("Component%f"), Towermesh->GetComponentRotation().Yaw);
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
		FVector diracthion = GetActorForwardVector();
		FVector locathion = GetActorLocation();
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *diracthion.ToString());
		TeleportTo(locathion + diracthion * Axis * (Speed * GetWorld()->GetDeltaSeconds()), GetActorRotation());
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
		RotateTower_OnServer(target);
	}
}

void ABaseTank::RotateTower_OnServer_Implementation(float Target)
{
	float math = InterpTo(Towermesh->GetRelativeRotation().Yaw, Target, GetWorld()->GetDeltaSeconds(), Towerrotation_speed);
	Towermesh->SetRelativeRotation(FRotator(0.0f, FMath::Clamp(math, -120.0f, 120.0f), 0.0f));
}

void ABaseTank::EnableAim()
{
	IsAim = true;
	camera->Deactivate();
	SecondCamera->Activate();
	ABaseHUD* HUD = GetController<APlayerController>()->GetHUD<ABaseHUD>();
	if (HUD != nullptr)
	{
		HUD->ToggleAim(true);
		//HUD->ToggleSuperPower(false);
	}
}

void ABaseTank::DisableAim()
{
	IsAim = false;
	SecondCamera->Deactivate();
	camera->Activate();
	ABaseHUD* HUD = GetController<APlayerController>()->GetHUD<ABaseHUD>();
	if (HUD != nullptr)
	{
		HUD->ToggleAim(false);
	//	HUD->ToggleSuperPower(true);
	}
}

void ABaseTank::Shoot_OnServer_Implementation()
{
	if (struction.objctBullet != nullptr && !isReload)
	{
		isReload = true;
		FActorSpawnParameters spawnParametars;
		spawnParametars.Owner = this;
		spawnParametars.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;

		Abullet* Ref_Bullet = GetWorld()->SpawnActor<Abullet>(struction.objctBullet, FTransform(bscene->GetComponentRotation(), bscene->GetComponentLocation(), FVector(1.0f, 1.0f, 1.0f)), spawnParametars);
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
	if (!IsAim && !HasAuthority())
	{
		//Spawn Explosion 
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), struction.Explosion, FTransform(bscene->GetComponentRotation(), bscene->GetComponentLocation(), FVector(0.6f, 0.6f, 0.6f)));
	}
	//Start Widget Timer
	if(Main_Widget != nullptr)
		Main_Widget->ReloadStats->Construct_Widget();
	//Spawn Sound
	UGameplayStatics::SpawnSoundAttached(struction.Shoot_sound, bscene);
	
}

void ABaseTank::RecharchShoot()
{
	isReload = false;
	Widget_ReloadShoot();
}

void ABaseTank::Widget_ReloadShoot_Implementation()
{
	if (Main_Widget != nullptr)
	{
		if (Main_Widget->ReloadStats != nullptr)
			Main_Widget->ReloadStats->FinishTimer();
	}
}

void ABaseTank::VisualDeadMulticast_Implementation()
{
	if (!HasAuthority())
	{
		Mesh->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
		Towermesh->SetCollisionEnabled(ECollisionEnabled::Type::PhysicsOnly);
		Towermesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);
		
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), struction.Explosion, FTransform(Towermesh->GetComponentRotation(), Towermesh->GetComponentLocation(), FVector(2.0f, 2.0f, 2.0f)));

		Towermesh->SetSimulatePhysics(true);
		Towermesh->AddImpulse(FVector(FMath::FRandRange(HP_Component->Impulse * -1, HP_Component->Impulse), FMath::FRandRange(HP_Component->Impulse * -1, HP_Component->Impulse), HP_Component->Impulse));
	}
}

void ABaseTank::Destroy()
{
	AActor::Destroy();
}

inline ABase_GameMode* ABaseTank::Get_GameMode(class AActor* Object)
{
	return Cast<ABase_GameMode>(UGameplayStatics::GetGameMode(Object));
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
	if (Current > Target - 4  && Current < Target + 4)
	{
		return Current + FMath::Clamp<float>(DeltaSpeed, 0, 1) * (Target - Current);
	}
	else
	{
		if (Current < Target)
			Current += DeltaSpeed;
		else if (Current > Target)
			Current -= DeltaSpeed;
	}
	return Current;
}

//TSubclassOf<UW_SuperPower> ABaseTank::GetSuperSkillWidget()
//{
//	//Cast<APlayerController>(GetController())->GetHUD<ABaseHUD>()->superskillWidgetClass =
//	return struction.superSkillWidgetClass;
//}
