// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <MyGAME2/BaseTank.h>
#include "Light_Tank.generated.h"



UCLASS()
class MYGAME2_API ALight_Tank : public ABaseTank
{
	GENERATED_BODY()
	
public:

	ALight_Tank();

	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);

	UFUNCTION(Server, Unreliable)
	void EnableSuperPower_OnServer();
	UFUNCTION(Client, Unreliable)
	void EnableSuperPower_OnClient();

	void DisableSuperPower_OnServer();
	UFUNCTION(Client, Unreliable)
	void DisableSuperPower_OnClient();

	void Disable_isSuperPower();
private:

	float Super_speed;

	float Super_rotationSpeed;

	float Super_TowerRotation_Speed;
};
