// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthStat.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class MYGAME2_API UHealthStat : public UActorComponent
{
	GENERATED_BODY()

public:
	UHealthStat();

	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = InitailizrProperty)
		float Max_HP;

	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_UpdateWidget)
		float Courrent_HP;
	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = Dead_OnOwnerClient)
		bool IsDead;

	class ABaseTank* owner;

	float Impulse;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
		
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
		void OnPlayerTakeAnyDamage(AActor* DamagedActor, float damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION()
		void OnRep_UpdateWidget();

	UFUNCTION()
		void Dead_OnOwnerClient();

	UFUNCTION(Server, Unreliable)
		void Dead_Server();

	UFUNCTION(Server, Unreliable)
		void InitailizrProperty();

};
