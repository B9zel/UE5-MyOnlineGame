
#pragma once

#include "CoreMinimal.h"
#include <MyGAME2/BaseTank.h>
#include "HeavyTank.generated.h"



UCLASS()
class MYGAME2_API AHeavyTank : public ABaseTank
{
	GENERATED_BODY()

protected:

	AHeavyTank();

	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UFUNCTION()
	void EnableSuperPower_OnClient();

	UFUNCTION(Server, Unreliable)
	void EnableSuperPower_OnServer();

	UFUNCTION(Server, Unreliable)
		void DisableSuperPower_OnServer();

	UFUNCTION(Server, Unreliable)
		void Shoot_Server();
	UFUNCTION(Client, Unreliable)
	void ToggleActivateSuperSkillWidget(bool isActivate);
	UFUNCTION(Client, Unreliable)
	void OnReloadSuperSkillWidget();

	void Disable_isSuperPower();
private:

	float SuperDamage_Multiply;

	bool isReload;
};
