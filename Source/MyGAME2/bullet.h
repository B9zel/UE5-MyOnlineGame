
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "bullet.generated.h"

UCLASS()
class MYGAME2_API Abullet : public AActor
{
	GENERATED_BODY()
	
public:	
	
	Abullet();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UBoxComponent* Box_collision;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UProjectileMovementComponent* ProjectileMovement;



	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UParticleSystem* iscra;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float TimeDestroy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Damage;
	

protected:
	
	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void BaginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void HitOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void Destroyer();
	UFUNCTION(Server, Unreliable) //BlueprintImplementableEvent, BlueprintCallable
	void ShowWidgetDamgeOnServer(const float ShowDamage,const FVector DestroyLocation);
	UFUNCTION(Client,Unreliable)
	void ShowWidgetDamgeOnClient(const float ShowDamage, const FVector DestroyLocation);
};
