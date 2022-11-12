
#include "BaseTank.h"
#include <Components/StaticMeshComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include <Components/InputComponent.h>
#include <Components/SceneComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include <Kismet/GameplayStatics.h>
#include <MyGAME2/PawnController.h>
#include <Net/UnrealNetwork.h>
#include "Heads_Stats.h"
#include "bullet.h"
#include "Widget_Reload.h"
#include "Game_Interface.h"
#include <MyGAME2/Game/Base_GameMode.h>


ABaseTank::ABaseTank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	Towermesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Towermesh"));
	Towermesh->SetupAttachment(Mesh);

	spring_arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("springarm"));
	spring_arm->SetupAttachment(Mesh);

	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("camera"));
	camera->SetupAttachment(spring_arm);

	bscene = CreateDefaultSubobject<USceneComponent>(TEXT("BScene"));
	bscene->SetupAttachment(Towermesh);

	SecondCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Second Camera"));
	SecondCamera->SetupAttachment(Towermesh);
	SecondCamera->bAutoActivate = false;

	component = CreateDefaultSubobject<UHeads_Stats>(TEXT("Heads_Stats"));

	projectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	
	OnTakeAnyDamage.AddDynamic(this, &ABaseTank::Take_Damage);
}

// Called when the game starts or when spawned
void ABaseTank::BeginPlay()
{
	Super::BeginPlay();

	/*if (Main_Widget == nullptr && !HasAuthority() && GetOwner() != nullptr)
	{
		Main_Widget	= Cast<APawnController>(GetOwner())->Game_Interface;
	}*/
	component->Max_HP = this->Max_HP;
}

// Called every frame
void ABaseTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
//	UE_LOG(LogTemp, Warning, TEXT("Releativ %f"), Towermesh->GetRelativeRotation().Yaw);
//	UE_LOG(LogTemp, Warning, TEXT("Component%f"), Towermesh->GetComponentRotation().Yaw);
	if (!component->IsDead)
	{
		ClientRotateTower(DeltaTime);
	}
}


void ABaseTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseTank::Take_Damage(AActor* DamagedActor, float damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	component->Courrent_HP -= FMath::Clamp(damage, 0.0f, component->Max_HP);

	if (component->Courrent_HP <= 0.0f && !component->IsDead)
	{	
		GameMode->Pawn_Dead(Cast<APlayerController>(GetController()), Cast<APlayerController>(InstigatedBy));

		FTimerHandle handle;
		GetWorldTimerManager().SetTimer(handle, this, &ABaseTank::Destroy, TimeDestroy, false);
		component->IsDead = true;
	}
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

void ABaseTank::ClientRotateTower(float DeltaTime)
{
	if (!HasAuthority())
	{
		target = GetControlRotation().Yaw - Mesh->GetComponentRotation().Yaw;
		
		if (target > 180)
		{
			target -= 360;
		}
		CallRotateTower(DeltaTime, target);
	}
}

void ABaseTank::CallRotateTower_Implementation(float deltatime, float Target)
{
	RotateTower_Implementation(deltatime, Target);
}

void ABaseTank::RotateTower_Implementation(float deltaTime, float Target)
{
	if (HasAuthority())
	{
		//math = FMath::FInterpTo(Towermesh->GetRelativeRotation().Yaw, Target, deltaTime, Towerrotation_speed);
		math = InterpTo(Towermesh->GetRelativeRotation().Yaw, Target, deltaTime, Towerrotation_speed);
		
		Towermesh->SetRelativeRotation(FRotator(0.0f, FMath::Clamp(math, -120.0f, 120.0f), 0.0f));
	}
}

void ABaseTank::EnableAim()
{
	IsAim = true;
	camera->Deactivate();
	SecondCamera->Activate();
}

void ABaseTank::DisableAim()
{
	IsAim = false;
	SecondCamera->Deactivate();
	camera->Activate();
}

void ABaseTank::Shoot_OnServer_Implementation()
{
	if (struction.objctBullet != nullptr && !blockShoot)
	{
		blockShoot = true;

		FActorSpawnParameters spawnParametars;
		spawnParametars.Owner = this;

		Abullet* Ref_Bullet = GetWorld()->SpawnActor<Abullet>(struction.objctBullet, FTransform(bscene->GetComponentRotation(), bscene->GetComponentLocation(), FVector(1.0f, 1.0f, 1.0f)), spawnParametars);
		Ref_Bullet->Damage = this->Damage;
		Shoot_Multicast();

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
	blockShoot = false;
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
		Towermesh->SetSimulatePhysics(true);

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), struction.Explosion, FTransform(Towermesh->GetComponentRotation(), Towermesh->GetComponentLocation(), FVector(2.0f, 2.0f, 2.0f)));

		Towermesh->AddImpulse(FVector(FMath::FRandRange(component->Impulse * -1, component->Impulse), FMath::FRandRange(component->Impulse * -1, component->Impulse), component->Impulse));

		Mesh->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
		Towermesh->SetCollisionEnabled(ECollisionEnabled::Type::PhysicsOnly);
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

float ABaseTank::Get_Damage()
{
	return Damage;
}

float ABaseTank::InterpTo(float Current, float Target, float DeltaTime, float speed)
{
	if (Current == Target)
		return Current;
	
	float DeltaSpeed = speed * DeltaTime;
	if (Current > Target - 2.f && Current < Target + 2.f)
	{
		return Current + DeltaSpeed * (Target - Current);
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