#pragma once

#include "CoreMinimal.h"
#include "BaseTankConfigDataAsset.h"
#include "DoubleDamageTankConfigDataAsset.generated.h"




UCLASS()
class MYGAME2_API UDoubleDamageTankConfigDataAsset : public UBaseTankConfigDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0"))
	float SuperDamage;
};