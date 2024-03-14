
#pragma once

#include "CoreMinimal.h"
#include <MyGAME2/BaseTank.h>
#include "Stealth_Tank.generated.h"




UCLASS()
class MYGAME2_API AStealth_Tank : public ABaseTank
{
	GENERATED_BODY()

public:
	//Methods
	AStealth_Tank();

	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);
	UFUNCTION()
	virtual void Take_Damage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

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
