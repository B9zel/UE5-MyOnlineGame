
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Heads_Stats.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYGAME2_API UHeads_Stats : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHeads_Stats();
	
	UPROPERTY(BlueprintReadWrite,ReplicatedUsing = InitailizrProperty)
	float Max_HP;

	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_UpdateWidget)
	float Courrent_HP;
	UPROPERTY(BlueprintReadWrite,ReplicatedUsing = Dead_OnOwnerClient)
	bool IsDead;

	class ABaseTank* owner;
	
	float Impulse;

	class AController* EnamyController;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void OnRep_UpdateWidget();
	
	UFUNCTION()
		void Dead_OnOwnerClient();

	UFUNCTION(Server, Unreliable)
		void Dead_Server();

	UFUNCTION(Server, Unreliable)
	void InitailizrProperty();

	UFUNCTION()
	void CallSpawnSpectator();
};
