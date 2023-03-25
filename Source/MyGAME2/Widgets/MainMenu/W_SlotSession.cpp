// Fill out your copyright notice in the Description page of Project Settings.


#include "W_SlotSession.h"
#include <Components/Button.h>
#include <Components/TextBlock.h>
#include <Interfaces/OnlineSessionInterface.h>
#include <OnlineSubsystem.h>

#include <Kismet/GameplayStatics.h>
#include "../../Game/BaseGameInstance.h"
#include <Input/Reply.h>



void UW_SlotSession::NativeConstruct()
{
	Super::NativeConstruct();
	
}

FReply UW_SlotSession::NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FKey key = "Left Mouse Button";
	
	if (InMouseEvent.IsMouseButtonDown(key))
	{
		Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(this))->joinSession(*SessionInfo, GetOwningPlayer());
	}
	
	return FReply::Handled();
}
