
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PlayerStatistic.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDispatcher);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDispatcherOneParams, ABaseTank*, Instigator);

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
	UPROPERTY(ReplicatedUsing = SwitchWidgetNames, BlueprintReadWrite)
		bool isAlive;
	

	FDispatcher PlayerAlive;
	FDispatcherOneParams PlayerDead;
public:

	
	UFUNCTION()
	void AddKill();
	UFUNCTION()
	void AddDeath();
	UFUNCTION(NetMulticast,Unreliable)
	void OnwerPawnDead(ABaseTank* Deadinstigator);

	UFUNCTION()
	void SwitchWidgetNames();
protected:
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
