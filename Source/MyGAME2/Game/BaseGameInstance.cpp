// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameInstance.h"
#include <OnlineSubsystem.h>
#include <OnlineSessionSettings.h>
#include <Kismet/GameplayStatics.h>
#include <Templates/SharedPointer.h>


UBaseGameInstance::UBaseGameInstance()
{
	IOnlineSubsystem* SubSystem = IOnlineSubsystem::Get();

	if (SubSystem != nullptr)
	{
		SessionInterface = SubSystem->GetSessionInterface();
	}
}

void UBaseGameInstance::joinSession(FOnlineSessionSearchResult& Session, APlayerController* controller)
{
	if (SessionInterface != nullptr)
	{
		if (SessionInterface != nullptr)
		{
			FString JoinAdress;
			SessionInterface->GetResolvedConnectString(FName(Session.Session.GetSessionIdStr()), JoinAdress);
			controller->ClientTravel(JoinAdress, TRAVEL_Absolute);
		}
		
	}
}

void UBaseGameInstance::joinSession(FString IP, APlayerController* controller)
{
	UKismetSystemLibrary::ExecuteConsoleCommand(this, FString("Open ") + IP, controller);
}

TArray<FOnlineSessionSearchResult> UBaseGameInstance::findSession(APlayerController* controller, bool LAN)
{
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	SessionSearch->bIsLanQuery = LAN;
	SessionSearch->MaxSearchResults = 100;
	SessionInterface->FindSessions(controller->GetUniqueID(), SessionSearch.ToSharedRef());

	return SessionSearch->SearchResults;
}
