// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <MyGAME2/BaseTank.h>
#include "Light_Tank.generated.h"


class ULightTankConfigDataAsset;


UCLASS()
class MYGAME2_API ALight_Tank : public ABaseTank
{
	GENERATED_BODY()
	
public:

	ALight_Tank();

public:

	UFUNCTION(Server, Unreliable)
	void EnableSuperPower_OnServer();
	UFUNCTION(Client, Unreliable)
	void EnableSuperPower_OnClient();

	void DisableSuperPower_OnServer();
	UFUNCTION(Client, Unreliable)
	void DisableSuperPower_OnClient();

	void Disable_isSuperPower();

protected:

	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);
	virtual void InitializeProperties() override;

protected:

	UPROPERTY(EditAnywhere)
	ULightTankConfigDataAsset* TankConfig;

private:

	float Super_rotationSpeed;
	float Super_TowerRotation_Speed;
	float Super_speed;

	float DefaultSpeed;
	float DefaultRotationSpeed;
	float DefaultTowerRotationSpeed;
};
