
#include "bullet.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include <Kismet/GameplayStatics.h>
#include <MyGAME2/Pawns/HeavyTank.h>
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

	//Box_collision->OnComponentHit.AddDynamic(this, &Abullet::OnHit);

	Box_collision->OnComponentBeginOverlap.AddDynamic(this, &Abullet::BaginOverlap);

	Box_collision->OnComponentHit.AddDynamic(this, &Abullet::OnHit);

	TimeDestroy = 3.0f;
}

// Called when the game starts or when spawned
void Abullet::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}

	FTimerHandle handle;
	GetWorldTimerManager().SetTimer(handle, this, &Abullet::Destroyer, TimeDestroy, false);
}

// Called every frame
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
	//	class ABaseTank* actor = Cast<ABaseTank>(OtherActor);
	TSubclassOf<UDamageType> typeDamage;

	if (GetOwner() != OtherActor)
	{
		if (HasAuthority())
		{
			UGameplayStatics::ApplyDamage(OtherActor, Damage, GetOwner()->GetInstigatorController(), this, typeDamage);
		}
		Destroy();

		UGameplayStatics::SpawnEmitterAtLocation(this->GetWorld(), iscra, FTransform(GetActorRotation(), GetActorLocation(), FVector(0.5f, 0.5f, 0.5f)));	
	}	
}

void Abullet::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Destroy();
}
