#pragma once

#include "CoreMinimal.h"
#include "BaseTankConfigDataAsset.h"
#include "InvisibleTankConfigDataAsset.generated.h"




UCLASS()
class MYGAME2_API UInvisibleTankConfigDataAsset : public UBaseTankConfigDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	UMaterialInterface* Material_InvisibleBase;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* Material_InvisibleTower;
};