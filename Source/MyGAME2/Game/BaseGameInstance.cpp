// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameInstance.h"
#include <OnlineSubsystem.h>
#include <OnlineSessionSettings.h>
#include <Kismet/GameplayStatics.h>
#include <Templates/SharedPointer.h>
#include "../Enums/E_PlayerSpace.h"
#include "Save/BaseSaveGame.h"


UBaseGameInstance::UBaseGameInstance()
{
	SaveSlotOptions = "Options";
	PlayerSpace = E_PlayerSpace::inMainSpace;
}

void UBaseGameInstance::Init()
{
	Super::Init();

	IOnlineSubsystem* SubSystem = IOnlineSubsystem::Get();
	if (SubSystem != nullptr)
	{
		SessionInterface = SubSystem->GetSessionInterface();
	}
	SaveObject = Cast<UBaseSaveGame>(UGameplayStatics::CreateSaveGameObject(UBaseSaveGame::StaticClass()));
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

UBaseSaveGame* UBaseGameInstance::GetLoadFromOptionsSlot(int UserIndex)
{
	return Cast<UBaseSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotOptions, UserIndex));
}

UBaseSaveGame* UBaseGameInstance::GetSaveObject() const
{
	return SaveObject;
}

FString UBaseGameInstance::GetNameSlotOptions() const
{
	return SaveSlotOptions;
}

void UBaseGameInstance::SaveObjectToSlot(UBaseSaveGame* object, int UserIndex)
{
	UGameplayStatics::SaveGameToSlot(object, GetNameSlotOptions(),UserIndex);
}
