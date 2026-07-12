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

	TB_serverName->SetText(FText::FromString(SessionInfo->Session.OwningUserName));
	TB_Ping->SetText(FText::FromString(FString::FromInt(SessionInfo->PingInMs)));
	const FString NumPlayers = FString::FromInt(SessionInfo->Session.SessionSettings.NumPublicConnections - SessionInfo->Session.NumOpenPublicConnections);
	const FString NumMaxPlayers = FString::FromInt(SessionInfo->Session.SessionSettings.NumPublicConnections);
	TB_players->SetText(FText::FromString(NumPlayers + "/" + NumMaxPlayers));


	B_Session->OnPressed.AddDynamic(this, &UW_SlotSession::OnPressesSession);
}

void UW_SlotSession::OnPressesSession()
{
	Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(this))->joinSession(*SessionInfo, GetOwningPlayer());
}


void UW_SlotSession::SetSessionSearchInfo(FOnlineSessionSearchResult* SessionSearchInfo)
{
	SessionInfo = SessionSearchInfo;
}