// Fill out your copyright notice in the Description page of Project Settings.


#include "W_PreRoundPlayers.h"
#include <Components/VerticalBox.h>
#include <Kismet/GameplayStatics.h>
#include <GameFramework/GameStateBase.h>
#include <GameFramework/PlayerState.h>
#include "W_PreRoundPlayer.h"


void UW_PreRoundPlayers::NativeConstruct()
{
	Super::NativeConstruct();

	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle, this, &UW_PreRoundPlayers::UpdatePlayerName, 1.0f, true);
}

void UW_PreRoundPlayers::UpdatePlayerName()
{
	VB_Players->ClearChildren();
	for (auto& el : UGameplayStatics::GetGameState(this)->PlayerArray)
	{
		UW_PreRoundPlayer* PreRoundPlayer = CreateWidget<class UW_PreRoundPlayer>(GetOwningPlayer(), WPreRoundPlayerClass);
		PreRoundPlayer->PlayerState = el.Get();
		VB_Players->AddChild(PreRoundPlayer);
	};
}

