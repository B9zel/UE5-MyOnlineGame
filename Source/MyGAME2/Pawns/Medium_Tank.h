// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <MyGAME2/BaseTank.h>
#include "Medium_Tank.generated.h"


UCLASS()
class MYGAME2_API AMedium_Tank : public ABaseTank
{
	GENERATED_BODY()
	
public:

	AMedium_Tank();

	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UFUNCTION(Server, Unreliable)
	void Enable_SuperPower_OnServer();
	UFUNCTION(NetMulticast, Unreliable)
	void Enable_SuperPower_NetMulticast();

	void Disable_SuperPower_OnServer();

	UFUNCTION(NetMulticast, Unreliable)
	void Disable_SuperPower_NetMulticast();

	void Disable_isSuperPower();
private:

	ECollisionEnabled::Type BeginCollsision;

	UMaterialInterface* BaseMaterial;

	UMaterialInterface* TowerMaterial;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInterface* BaseMaterial_NotCollision;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInterface* TowerMaterial_NotCollision;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ECollisionChannel> Collision;
};	
