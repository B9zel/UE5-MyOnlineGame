// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <MyGAME2/BaseTank.h>
#include "Medium_Tank.generated.h"



class UGhostTankConfigDataAsset;

UCLASS()
class MYGAME2_API AMedium_Tank : public ABaseTank
{
	GENERATED_BODY()
	
public:

	AMedium_Tank();

public:

	UFUNCTION(Server, Unreliable)
	void Enable_SuperPower_OnServer();
	UFUNCTION(NetMulticast, Unreliable)
	void Enable_SuperPower_NetMulticast();
	UFUNCTION(Client, Unreliable)
	void EnableSuperPower_OnClient();

	void Disable_SuperPower_OnServer();

	UFUNCTION(NetMulticast, Unreliable)
	void Disable_SuperPower_NetMulticast();
	UFUNCTION(Client, Unreliable)
		void DisableSuperPower_OnClient();

	void Disable_isSuperPower();

protected:

	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void InitializeProperties() override;

public:

	UPROPERTY(EditAnywhere)
	UGhostTankConfigDataAsset* TankConfig;

private:

	ECollisionEnabled::Type BeginCollision;

	UMaterialInterface* BaseMaterial;
	UMaterialInterface* TowerMaterial;

	UMaterialInterface* BaseMaterial_NotCollision;
	UMaterialInterface* TowerMaterial_NotCollision;
	TEnumAsByte<ECollisionChannel> Collision;
};	
