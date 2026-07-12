// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BaseTankConfigDataAsset.generated.h"




UCLASS()
class MYGAME2_API UBaseTankConfigDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	FText Name;


	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0"))
	float Damage;
	
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0"))
	float Speed;

	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0"))
	float RotationSpeed;

	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0"))
	float TowerRotationSpeed;

	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0"))
	float HealthPoints;

	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0"))
	float TimeReload;

	UPROPERTY(EditAnywhere)
	FText SkillDescription;

	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0"))
	float SkillTimeUse;

	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0"))
	float SkillTimeReload;

	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0"))
	float TimeDestroyAfterDeath;

};
