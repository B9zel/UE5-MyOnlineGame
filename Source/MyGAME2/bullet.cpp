
#include "bullet.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include <Kismet/GameplayStatics.h>
#include <MyGAME2/HealthStat.h>
#include "BaseTank.h"


Abullet::Abullet()
{
	PrimaryActorTick.bCanEverTick = false;

	Box_collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box_collision;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Box_collision);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));

	ProjectileMovement->ProjectileGravityScale = 0.2f;

	Box_collision->OnComponentBeginOverlap.AddDynamic(this, &Abullet::BaginOverlap);
	Box_collision->OnComponentHit.AddDynamic(this, &Abullet::HitOverlap);

	TimeDestroy = 3.0f;
}

void Abullet::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);

		Damage = Cast<ABaseTank>(GetOwner())->GetDamage();
	}
	
	FTimerHandle handle;
	GetWorldTimerManager().SetTimer(handle, this, &Abullet::Destroyer, TimeDestroy, false);
}

void Abullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void Abullet::Destroyer()
{
	Destroy();
}

void Abullet::BaginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	class ABaseTank* pawn = Cast<ABaseTank>(OtherActor);
	
	if (pawn != nullptr)
	{
		if (pawn->HP_Component->IsDead)
			return;

		if (GetOwner() != pawn)
		{
			if (HasAuthority())
			{
				TSubclassOf<UDamageType> typeDamage;
				UGameplayStatics::ApplyDamage(pawn, Damage, GetOwner()->GetInstigatorController(), this, typeDamage);
				ShowDamgeOnServer(Damage, GetActorLocation());
			}
			else
			{
				UGameplayStatics::SpawnEmitterAtLocation(this->GetWorld(), iscra, FTransform(GetActorRotation(), GetActorLocation(), FVector(0.5f, 0.5f, 0.5f)));
			}
			Destroy();
		}

	}
	else
	{
		Destroy();
	}
}

void Abullet::HitOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//For collision with walls
	Destroy();
}
