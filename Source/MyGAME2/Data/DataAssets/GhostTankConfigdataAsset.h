#pragma once

#include "CoreMinimal.h"
#include "BaseTankConfigDataAsset.h"
#include "GhostTankConfigDataAsset.generated.h"




UCLASS()
class MYGAME2_API UGhostTankConfigDataAsset : public UBaseTankConfigDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	UMaterialInterface* BaseMaterial_NotCollision;
	UPROPERTY(EditAnywhere)
	UMaterialInterface* TowerMaterial_NotCollision;
	UPROPERTY(EditAnywhere)
	TEnumAsByte<ECollisionChannel> Collision;

};