#pragma once

#include "CoreMinimal.h"
#include "BaseTankConfigDataAsset.h"
#include "LightTankConfigDataAsset.generated.h"




UCLASS()
class MYGAME2_API ULightTankConfigDataAsset : public UBaseTankConfigDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0"))
	float SkillSpeed;
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0"))
	float SkillRotationSpeed;
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0"))
	float SkillTowerRotationSpeed;

};