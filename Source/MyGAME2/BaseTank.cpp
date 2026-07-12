
#include "BaseTank.h"
#include "bullet.h"
#include "Data/DataAssets/BaseTankConfigDataAsset.h"
#include "Game/Base_GameMode.h"
#include "Game/BaseHUD.h"
#include "Game_Interface.h"
#include "HealthStat.h"
#include "PawnController.h"
#include <Camera/CameraComponent.h>
#include <Components/AudioComponent.h>
#include <Components/SceneComponent.h>
#include <Components/StaticMeshComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <Kismet/GameplayStatics.h>
#include <Net/UnrealNetwork.h>
#include <NiagaraComponent.h>
#include <NiagaraFunctionLibrary.h>
#include <NiagaraSystem.h>


DECLARE_LOG_CATEGORY_CLASS(Tank, All, All);


ABaseTank::ABaseTank()
{
	PrimaryActorTick.bCanEverTick = true;

	SetReplicateMovement(false);

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

	N_ExplosionShoot = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Shoot emitter"));
	N_ExplosionShoot->SetupAttachment(bscene);
	N_ExplosionShoot->SetAutoActivate(false);

	SecondCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Second Camera"));
	SecondCamera->SetupAttachment(Towermesh);
	SecondCamera->bAutoActivate = false;
	SecondCamera->SetVisibility(false);

	HP_Component = CreateDefaultSubobject<UHealthStat>(TEXT("HealthStat"));

	Direction = EDirectionMove::STOP;
	MaxDistanceOutOfSyncRotation = 50.0f;
	MaxDistanceOutOfSyncLocation = 50.0f;
	MaxDegressOutOfSyncRotation = 5.0f;
}

void ABaseTank::PossessedBy(AController* controller)
{
	Super::PossessedBy(controller);

	controller->ClientSetRotation(Towermesh->GetComponentRotation());
}

void ABaseTank::BeginPlay()
{
	Super::BeginPlay();

	InitializeProperties();


	TargetYawRotation = Towermesh->GetRelativeRotation().Yaw;
	// Client
	if (!HasAuthority())
	{
		HUD = GetController<APlayerController>() != nullptr ? GetController<APlayerController>()->GetHUD<ABaseHUD>() : nullptr;
		if (HUD != nullptr)
		{
			HUD->superskillWidgetClass = struction.superSkillWidgetClass;
			HUD->CreateAimWidget();
		}
	}
	// Server
	else
	{
		gameMode = Cast<ABase_GameMode>(UGameplayStatics::GetGameMode(this));
		TargetLocation = GetActorLocation();
		TargetRotation = GetActorRotation();
	}

	D_SpawnTankPawn.Broadcast(this);
}

void ABaseTank::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (HUD != nullptr)
	{
		HUD->RemoveAimWidget();
	}
}


void ABaseTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!HasAuthority() && !HP_Component->IsDead)
	{
		ClientRotateTower();
		Move_OnClient();


	}



	switch (Direction)
	{
	case EDirectionMove::FORWARD_MOVE:
		ForwardMove();
		break;
	case EDirectionMove::BACK_MOVE:
		BackMove();
		break;
	case EDirectionMove::RIGHT_TURN:
		RightTurn();
		break;
	case EDirectionMove::LEFT_TURN:
		LeftTurn();
		break;
	case EDirectionMove::FORWARD_RIGHT_MOVE:
		RightTurn();
		ForwardMove();
		break;
	case EDirectionMove::FORWARD_LEFT_MOVE:
		LeftTurn();
		ForwardMove();
		break;
	case EDirectionMove::BACK_RIGHT_MOVE:
		RightTurn();
		BackMove();
		break;
	case EDirectionMove::BACK_LEFT_MOVE:
		LeftTurn();
		BackMove();
		break;
	default:
		break;
	}

}

void ABaseTank::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABaseTank, isReload);
	DOREPLIFETIME(ABaseTank, TargetYawRotation);
	DOREPLIFETIME(ABaseTank, TargetLocation);
	DOREPLIFETIME(ABaseTank, TargetRotation);
}


void ABaseTank::ForwardInputMove(float Axis)
{
	if (Axis > 0.0f)
	{
		ForwardMove_OnClient(Axis);
	}
	else if (Axis < 0.0f)
	{
		BackMove_OnClient(Axis);
	}
	else
	{
		ForwardMove_OnClient(Axis);
		BackMove_OnClient(Axis);
	}
}

void ABaseTank::RotateInputMove(float Axis)
{
	if (Axis > 0.0f)
	{
		RightTurn_Server(Axis);
	}
	else if (Axis < 0.0f)
	{
		LeftTurn_Server(Axis);
	}
	else
	{
		RightTurn_Server(Axis);
		LeftTurn_Server(Axis);
	}
}

void ABaseTank::ForwardMove_OnClient(float Axis)
{
	bool IsChangeDirection = false;
	if (Axis == 0.0f)
	{
		if (Direction == EDirectionMove::FORWARD_MOVE)
		{
			Direction = EDirectionMove::STOP;
			IsChangeDirection = true;
		}
		else if (Direction == EDirectionMove::FORWARD_RIGHT_MOVE)
		{
			Direction = EDirectionMove::RIGHT_TURN;
			IsChangeDirection = true;
		}
		else if (Direction == EDirectionMove::FORWARD_LEFT_MOVE)
		{
			Direction = EDirectionMove::LEFT_TURN;
			IsChangeDirection = true;
		}
	}
	else
	{
		if (Direction == EDirectionMove::RIGHT_TURN)
		{
			Direction = EDirectionMove::FORWARD_RIGHT_MOVE;
			IsChangeDirection = true;
		}
		else if (Direction == EDirectionMove::LEFT_TURN)
		{
			Direction = EDirectionMove::FORWARD_LEFT_MOVE;
			IsChangeDirection = true;
		}
		else if (Direction != EDirectionMove::FORWARD_MOVE && Direction != EDirectionMove::FORWARD_RIGHT_MOVE && Direction != EDirectionMove::FORWARD_LEFT_MOVE)
		{
			Direction = EDirectionMove::FORWARD_MOVE;
			IsChangeDirection = true;
		}
	}
	if (IsChangeDirection)
	{
		ChangeMoveDirection_Server(Direction);
	}
}

void ABaseTank::BackMove_OnClient(float Axis)
{
	bool IsChangeDirection = false;
	if (Axis == 0.0f)
	{
		if (Direction == EDirectionMove::BACK_MOVE)
		{
			Direction = EDirectionMove::STOP;
			IsChangeDirection = true;
		}
		else if (Direction == EDirectionMove::BACK_RIGHT_MOVE)
		{
			Direction = EDirectionMove::RIGHT_TURN;
			IsChangeDirection = true;
		}
		else if (Direction == EDirectionMove::BACK_LEFT_MOVE)
		{
			Direction = EDirectionMove::LEFT_TURN;
			IsChangeDirection = true;
		}
	}
	else
	{
		if (Direction == EDirectionMove::RIGHT_TURN)
		{
			Direction = EDirectionMove::BACK_RIGHT_MOVE;
			IsChangeDirection = true;
		}
		else if (Direction == EDirectionMove::LEFT_TURN)
		{
			Direction = EDirectionMove::BACK_LEFT_MOVE;
			IsChangeDirection = true;
		}
		else if (Direction != EDirectionMove::BACK_MOVE && Direction != EDirectionMove::BACK_RIGHT_MOVE && Direction != EDirectionMove::BACK_LEFT_MOVE)
		{
			Direction = EDirectionMove::BACK_MOVE;
			IsChangeDirection = true;
		}
	}
	if (IsChangeDirection)
	{
		ChangeMoveDirection_Server(Direction);
	}
}

void ABaseTank::ChangeMoveDirection_Server_Implementation(EDirectionMove NewDirection)
{
	Direction = NewDirection;
}

void ABaseTank::ForwardMove()
{
	FVector diraction = GetActorLocation() + GetActorForwardVector() * (Speed * GetWorld()->GetDeltaSeconds());

	TeleportTo(diraction, GetActorRotation());

	TargetLocation = GetActorLocation();
}

void ABaseTank::BackMove()
{
	FVector diraction = GetActorLocation() + -GetActorForwardVector() * (Speed * GetWorld()->GetDeltaSeconds());

	TeleportTo(diraction, GetActorRotation());

	TargetLocation = GetActorLocation();
}

void ABaseTank::RightTurn_Server(float Axis)
{
	bool IsChangeDirection = false;
	if (Axis == 0.0f)
	{
		if (Direction == EDirectionMove::RIGHT_TURN)
		{
			Direction = EDirectionMove::STOP;
			IsChangeDirection = true;
		}
		else if (Direction == EDirectionMove::FORWARD_RIGHT_MOVE)
		{
			Direction = EDirectionMove::FORWARD_MOVE;
			IsChangeDirection = true;
		}
		else if (Direction == EDirectionMove::BACK_RIGHT_MOVE)
		{
			Direction = EDirectionMove::BACK_MOVE;
			IsChangeDirection = true;
		}
	}
	else
	{
		if (Direction == EDirectionMove::FORWARD_MOVE)
		{
			Direction = EDirectionMove::FORWARD_RIGHT_MOVE;

			IsChangeDirection = true;
		}
		else if (Direction == EDirectionMove::BACK_MOVE)
		{
			Direction = EDirectionMove::BACK_RIGHT_MOVE;
			IsChangeDirection = true;
		}
		else if (Direction != EDirectionMove::RIGHT_TURN && Direction != EDirectionMove::FORWARD_RIGHT_MOVE && Direction != EDirectionMove::BACK_RIGHT_MOVE)
		{
			Direction = EDirectionMove::RIGHT_TURN;
			IsChangeDirection = true;
		}
	}
	if (IsChangeDirection)
	{
		ChangeMoveDirection_Server(Direction);
	}
}

void ABaseTank::LeftTurn_Server(float Axis)
{
	bool IsChangeDirection = false;
	if (Axis == 0.0f)
	{
		if (Direction == EDirectionMove::LEFT_TURN)
		{
			Direction = EDirectionMove::STOP;
			IsChangeDirection = true;
		}
		else if (Direction == EDirectionMove::FORWARD_LEFT_MOVE)
		{
			Direction = EDirectionMove::FORWARD_MOVE;
			IsChangeDirection = true;
		}
		else if (Direction == EDirectionMove::BACK_LEFT_MOVE)
		{
			Direction = EDirectionMove::BACK_MOVE;
			IsChangeDirection = true;
		}
	}
	else
	{
		if (Direction == EDirectionMove::FORWARD_MOVE)
		{
			Direction = EDirectionMove::FORWARD_LEFT_MOVE;
			IsChangeDirection = true;
		}
		else if (Direction == EDirectionMove::BACK_MOVE)
		{
			Direction = EDirectionMove::BACK_LEFT_MOVE;
			IsChangeDirection = true;
		}
		else if (Direction != EDirectionMove::LEFT_TURN && Direction != EDirectionMove::FORWARD_LEFT_MOVE && Direction != EDirectionMove::BACK_LEFT_MOVE)
		{
			Direction = EDirectionMove::LEFT_TURN;
			IsChangeDirection = true;
		}
	}
	if (IsChangeDirection)
	{
		ChangeMoveDirection_Server(Direction);
	}
}

void ABaseTank::RightTurn()
{
	FRotator direction = GetActorRotation();
	const float NewYaw = direction.Yaw + Rotation_speed * GetWorld()->GetDeltaSeconds();

	TeleportTo(GetActorLocation(), FRotator(direction.Pitch, NewYaw, direction.Roll));
	UE_LOG(LogTemp, Display, TEXT("NewYaw: %f"), NewYaw);
	UE_LOG(LogTemp, Display, TEXT("TowerRotation: %f"), TargetYawRotation - NewYaw);

	TargetRotation = GetActorRotation();

	TargetYawRotation -= FMath::Abs(TargetRotation.Yaw - direction.Yaw);
	SetTowerRotation_OnClient(TargetYawRotation);
}


void ABaseTank::LeftTurn()
{
	FRotator direction = GetActorRotation();
	const float NewYaw = direction.Yaw - Rotation_speed * GetWorld()->GetDeltaSeconds();

	TeleportTo(GetActorLocation(), FRotator(direction.Pitch, NewYaw, direction.Roll));

	UE_LOG(LogTemp, Display, TEXT("NewYaw: %f"), NewYaw);
	UE_LOG(LogTemp, Display, TEXT("TowerRotation: %f"), TargetYawRotation - NewYaw);

	TargetRotation = GetActorRotation();
	TargetYawRotation += FMath::Abs(TargetRotation.Yaw - direction.Yaw);
	SetTowerRotation_OnClient(TargetYawRotation);
}

void ABaseTank::ClientRotateTower()
{
	//const FRotator& CurrentTowerRotation = Towermesh->GetRelativeRotation();
	//if (FMath::Abs(CurrentTowerRotation.Yaw - TargetYawRotation) > MaxDegressOutOfSyncRotation)
	//{
	//	Towermesh->SetRelativeRotation(FRotator(0.0f, FMath::Clamp(TargetYawRotation, MinDigressRotateTower, MaxDigressRotateTower), 0.0f));
	//}
	//else
	//{
	//}
	Towermesh->SetRelativeRotation(FRotator(0.0f, FMath::Clamp(InterpTo(Towermesh->GetRelativeRotation().Yaw, TargetYawRotation, GetWorld()->GetDeltaSeconds(), Towerrotation_speed), MinDigressRotateTower, MaxDigressRotateTower), 0.0f));


	if (IsLocallyControlled())
	{
		if (!(FMath::Abs(FMath::FindDeltaAngleDegrees(Mesh->GetRelativeRotation().Yaw, GetControlRotation().Yaw)) < 1.0f))
		{
			RotateTower_OnServer(GetControlRotation().Yaw);
		}
	}
}

void ABaseTank::Move_OnClient()
{
	const FVector Location = GetActorLocation();
	const FRotator Rotation = GetActorRotation();

	if (Location != TargetLocation || Rotation != TargetRotation)
	{
		if (FVector::Dist(Location, TargetLocation) >= MaxDistanceOutOfSyncLocation)
		{
			TeleportTo(TargetLocation, TargetRotation);
		}
		else
		{
			const FVector& InterpLocation = FMath::VInterpTo(Location, TargetLocation, GetWorld()->GetDeltaSeconds(), Speed);
			const FRotator& InterpRotation = FMath::RInterpTo(Rotation, TargetRotation, GetWorld()->GetDeltaSeconds(), Rotation_speed);
			SetActorLocationAndRotation(InterpLocation, InterpRotation);
		}

	}
}

void ABaseTank::RotateTower_OnServer_Implementation(float Yaw)
{
	float DeltaRotate = Mesh->GetRelativeRotation().Yaw;
	float target = FMath::FindDeltaAngleDegrees(DeltaRotate, Yaw);

	TargetYawRotation = FMath::Clamp(target, MinDigressRotateTower, MaxDigressRotateTower);
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

void ABaseTank::Shoot()
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, FString::Printf(TEXT("Client: shoot Yaw: %f"), Towermesh->GetRelativeRotation().Yaw));

	Shoot_OnServer(Towermesh->GetRelativeRotation().Yaw);
}

void ABaseTank::Shoot_OnServer_Implementation(float YawRotateTower)
{
	UE_LOG(Tank, Display, TEXT("Call Shoot_OnServer"))
		if (struction.objectBullet != nullptr && !isReload)
		{
			isReload = true;

			Towermesh->SetRelativeRotation(FRotator(0.0f, YawRotateTower, 0.0f));

			FActorSpawnParameters spawnParametars;
			spawnParametars.Owner = this;
			UE_LOG(Tank, Display, TEXT("Shoot_OnServer: Pre spawn bullet"));
			Abullet* Ref_Bullet = GetWorld()->SpawnActor<Abullet>(struction.objectBullet, FTransform(bscene->GetComponentRotation(), bscene->GetComponentLocation(), FVector(1.0f, 1.0f, 1.0f)), spawnParametars);
			UE_LOG(Tank, Display, TEXT("Shoot_OnServer: Post spawn bullet"));
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
	UE_LOG(Tank, Display, TEXT("Call Shoot_Multicast"))
		if (!HasAuthority())
		{
			if (!IsAim)
			{
				UE_LOG(Tank, Display, TEXT("Shoot_Multicast: Pre naigara"));
				//Spawn Explosion 
				N_ExplosionShoot->ActivateSystem();
				UE_LOG(Tank, Display, TEXT("Shoot_Multicast: Post naigara"));
			}

			//Start Widget Timer
			D_ReloadStart.Broadcast(TimeReload, 0.1f, 0.1f);

			UE_LOG(Tank, Display, TEXT("Shoot_Multicast: Pre audio"));
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
	D_ReloadEnd.Broadcast();
}

void ABaseTank::VisualDeadMulticast_Implementation()
{
	if (!HasAuthority())
	{
		Mesh->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
		Towermesh->SetCollisionEnabled(ECollisionEnabled::Type::PhysicsOnly);
		Towermesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);

		//Spawn Niagara
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

	if (FMath::Abs(Target - Current) < 2.0f)
	{
		return Current + FMath::Clamp<float>(DeltaSpeed, 0, 1) * (Target - Current);
	}
	else
	{
		if (Current < Target)
		{
			return Current + FMath::Clamp<float>(DeltaSpeed, 0, 1);
		}
		else
		{
			return Current - FMath::Clamp<float>(DeltaSpeed, 0, 1);
		}
	}
}

void ABaseTank::SetTowerRotationServer(const float YawValue)
{
	RotateTower_OnServer(YawValue);
	SetTowerRotation_OnClient(TargetYawRotation);
}


void ABaseTank::SetTowerRotation_OnClient_Implementation(const float ValueYaw)
{
	if (FMath::Abs(Towermesh->GetRelativeRotation().Yaw - TargetYawRotation) < 0.5f)
	{
		Towermesh->SetRelativeRotation(FRotator(0.0f, FMath::Clamp(ValueYaw, MinDigressRotateTower, MaxDigressRotateTower), 0.0f));
	}
}
