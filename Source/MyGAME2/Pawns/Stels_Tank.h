
#pragma once

#include "CoreMinimal.h"
#include <MyGAME2/BaseTank.h>
#include "Stels_Tank.generated.h"




UCLASS()
class MYGAME2_API AStels_Tank : public ABaseTank
{
	GENERATED_BODY()

public:
	//Methods
	AStels_Tank();

	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);

	virtual void Take_Damage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(Client, Unreliable)
	void EnableSuperPower_OnClient();
	UFUNCTION(Server, Unreliable)
	void EnableSuperPower_OnServer();
	UFUNCTION(NetMulticast, Unreliable)
	void EnableSuperPower_Multicast();

	void DisableSuperPower_OnClient();
	UFUNCTION(NetMulticast, Unreliable)
	void DisableSuperPower_Multicast();

	inline void EnableUse_SuperPower();

	void StartReload_SuperPower_OnServer();
public:
	//Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMaterialInterface* Material_Base;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMaterialInterface* Material_BaseTower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMaterialInterface* Material_InvisibleBase;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMaterialInterface* Material_InvisibleTower;

	
private:

	FTimerHandle TimerKey;

	UPROPERTY(Replicated)
		bool isUseSuper_Power;
};
