
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_EndRoundMapVote.generated.h"




UCLASS()
class MYGAME2_API UW_EndRoundMapVote : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(meta = (BindWidget))
	class UScrollBox* SB_Maps;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UW_EndRoundMap> EndRoundMapWidget;
protected:

	virtual void NativeConstruct() override;

	UFUNCTION()
	void CreateToVoteMap(TArray<FName> MapNames);
};
