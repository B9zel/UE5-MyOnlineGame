
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PlayerStatistic.generated.h"



UCLASS()
class MYGAME2_API APlayerStatistic : public APlayerState
{
	GENERATED_BODY()

public:
	
	APlayerStatistic();

	UPROPERTY(Replicated,BlueprintReadWrite)
		int Kills;
	UPROPERTY(Replicated,BlueprintReadWrite)
		int Deaths;
	
public:
	UFUNCTION()
	void AddKill();
	UFUNCTION()
	void AddDeath();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
