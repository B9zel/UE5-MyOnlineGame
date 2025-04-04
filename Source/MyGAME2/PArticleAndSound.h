// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PArticleAndSound.generated.h"

UCLASS()
class MYGAME2_API APArticleAndSound : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APArticleAndSound();

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//UParticleSystemComponent* ParticleComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UNiagaraComponent* NiagaraComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAudioComponent* AudioComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Destroyer();
};
