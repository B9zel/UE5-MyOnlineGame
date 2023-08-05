// Fill out your copyright notice in the Description page of Project Settings.


#include "PArticleAndSound.h"
#include <particles/ParticleSystemComponent.h>
//#include <NiagaraComponent.h>
#include <NiagaraComponent.h>
#include <Components/AudioComponent.h>

// Sets default values
APArticleAndSound::APArticleAndSound()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	///ParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Partical system"));
	//ParticleComponent->SetupAttachment(RootComponent);

	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara system"));
	NiagaraComponent->SetupAttachment(RootComponent);


	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Component"));
	AudioComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void APArticleAndSound::BeginPlay()
{
	Super::BeginPlay();

	
	
	FTimerHandle handle;
	GetWorldTimerManager().SetTimer(handle, this, &APArticleAndSound::Destroyer,3.0f, false);
}

// Called every frame
void APArticleAndSound::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APArticleAndSound::Destroyer()
{
	Destroy();
}