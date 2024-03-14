
#pragma once

#include "CoreMinimal.h"
//#include "UObject/NoExportTypes.h"
#include <Engine/DataTable.h>
#include "ST_MapInfo.generated.h"



USTRUCT(BlueprintType)
struct FST_MapInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText NameMap;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText ShowNameMap;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* Icon;
	
};


//UCLASS()
//class MYGAME2_API UST_MapInfo : public UObject
//{
//	GENERATED_BODY()
//	
//};
