
#pragma once

#include "CoreMinimal.h"
#include <MyGAME2/BaseTank.h>
#include "HeavyTank.generated.h"




class UDoubleDamageTankConfigDataAsset;


UCLASS()
class MYGAME2_API AHeavyTank : public ABaseTank
{
	GENERATED_BODY()

protected:

	AHeavyTank();

	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void InitializeProperties() override;
	
	UFUNCTION()
	void EnableSuperPower_OnClient();

	UFUNCTION(Server, Unreliable)
	void EnableSuperPower_OnServer();

	UFUNCTION()
	void DisableSuperPower_OnServer();

	UFUNCTION(Server, Unreliable)
		void Shoot_Server(float YawRotateTower);
	UFUNCTION(Client, Unreliable)
	void ToggleActivateSuperSkillWidget(bool isActivate);
	UFUNCTION(Client, Unreliable)
	void OnReloadSuperSkillWidget();

	 void DisableReloadSuperPower();
public:

	 float GetSuperDamage();

protected:

	UPROPERTY(EditAnywhere)
	UDoubleDamageTankConfigDataAsset* TankConfig;

private:

	float StandartDamage;
	float SuperDamage;
};
