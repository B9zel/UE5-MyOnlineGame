// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameInstance.h"
#include <OnlineSubsystem.h>
#include <Kismet/GameplayStatics.h>
#include <Engine/LocalPlayer.h>
#include <GameFramework/PlayerController.h>
#include "Online/OnlineSessionNames.h"

#include "Save/BaseSaveGame.h"



DECLARE_LOG_CATEGORY_CLASS(GameInstance, All, All);


UBaseGameInstance::UBaseGameInstance()
{
	SaveSlotOptions = "Options";
	PlayerSpace = E_PlayerSpace::inMainSpace;
	SessionName = NAME_GameSession;
}

void UBaseGameInstance::Init()
{
	Super::Init();

	if (IsDedicatedServerInstance())
	{
		DelegateCreateSessionComplete.BindUObject(this, &UBaseGameInstance::OnCreateSession);
	}
	DelegateCancelSessionComplete.BindUObject(this, &UBaseGameInstance::OnCancelFindSession);
	DelegateFindSesssionComplete.BindUObject(this, &UBaseGameInstance::OnFindSessionComplete);
	DelegateJoinSessionComplete.BindUObject(this, &UBaseGameInstance::OnJoinSession);
	CreateSession();
}

void UBaseGameInstance::CreateSession()
{
	if (IsDedicatedServerInstance())
	{
		SubSystem = IOnlineSubsystem::Get();
		if (SubSystem != nullptr)
		{
			UE_LOG(GameInstance, Display, TEXT("Get online subsystem"));
			SessionInterface = SubSystem->GetSessionInterface();

			SessionInterface->AddOnCreateSessionCompleteDelegate_Handle(DelegateCreateSessionComplete);
			if (SessionInterface)
			{
				UE_LOG(GameInstance, Display, TEXT("Get session interface"));
			}
			if (SessionInterface->GetNamedSession(SessionName))
			{
				UE_LOG(GameInstance, Display, TEXT("Destroy session"));
				SessionInterface->DestroySession(SessionName);
			}
			FOnlineSessionSettings Settings;
			Settings.bAllowInvites = true;
			Settings.bIsDedicated = true;
			Settings.bIsLANMatch = true;
			Settings.bAllowJoinInProgress = true;
			Settings.bAllowJoinViaPresence = true;
			Settings.bUsesPresence = true;
			Settings.bShouldAdvertise = true;
			Settings.bUseLobbiesIfAvailable = true;
			Settings.NumPublicConnections = 4;

			SessionInterface->CreateSession(0, SessionName, Settings);

		}
	}
}

void UBaseGameInstance::joinSession(FOnlineSessionSearchResult& Session, APlayerController* controller)
{
	if (!SessionInterface)
	{
		if (!SubSystem)
		{
			SubSystem = IOnlineSubsystem::Get();
		}
		SessionInterface = SubSystem->GetSessionInterface();
	}
	if (SessionInterface != nullptr)
	{
		UE_LOG(GameInstance, Display, TEXT("Join Session"));
		SessionInterface->AddOnJoinSessionCompleteDelegate_Handle(DelegateJoinSessionComplete);
		JoinController = controller;
		JoinSession = &Session;

		SessionInterface->JoinSession(*controller->GetLocalPlayer()->GetPreferredUniqueNetId(), SessionName, Session);
	}
}

void UBaseGameInstance::joinSession(FString IP, APlayerController* controller)
{
	UKismetSystemLibrary::ExecuteConsoleCommand(this, FString("Open ") + IP, controller);
}

void UBaseGameInstance::findSession(APlayerController* controller, bool LAN)
{
	if (!SessionInterface.IsValid())
	{
		if (auto* OnlineSubsystem = IOnlineSubsystem::Get())
		{
			SessionInterface = OnlineSubsystem->GetSessionInterface();
		}
		else
		{
			return;
		}
	}
	UE_LOG(GameInstance, Display, TEXT("Find session"));
	UE_LOG(GameInstance, Display, TEXT("Before Valid search"));

	if (!SessionSearch.IsValid())
	{
		UE_LOG(GameInstance, Display, TEXT("After Valid search"));
		SessionSearch = MakeShared<FOnlineSessionSearch>();
		UE_LOG(GameInstance, Display, TEXT("After Create search"));

		SessionInterface->AddOnCancelFindSessionsCompleteDelegate_Handle(DelegateCancelSessionComplete);
		SessionInterface->AddOnFindSessionsCompleteDelegate_Handle(DelegateFindSesssionComplete);
	}
	UE_LOG(GameInstance, Display, TEXT("init search LAN: %d"), LAN);
	SessionSearch->bIsLanQuery = LAN;
	SessionSearch->MaxSearchResults = 10;
	SessionSearch->QuerySettings.Set(SEARCH_LOBBIES, true, EOnlineComparisonOp::Equals);

	ULocalPlayer* localPlayer = controller->GetLocalPlayer();
	auto& id = (*localPlayer->GetPreferredUniqueNetId());
	UE_LOG(GameInstance, Display, TEXT("GetPreferredUniqueNetId: %s"), *id.ToString());

	SessionInterface->FindSessions(*localPlayer->GetPreferredUniqueNetId(), SessionSearch.ToSharedRef());
}

void UBaseGameInstance::OnFindSessionComplete(bool IsWasFound)
{
	UE_LOG(GameInstance, Display, TEXT("Find session complete %d"), IsWasFound);
	if (IsWasFound)
	{
		FindSessionCompleteDelegate.Broadcast(SessionSearch->SearchResults);
	}
}

void UBaseGameInstance::OnCancelFindSession(bool IsCancel)
{
	UE_LOG(GameInstance, Display, TEXT("Cancel find session"));
	CancelFindSessionCompleteDelegate.Broadcast();
}

void UBaseGameInstance::OnCreateSession(FName sessionName, bool IsCreate)
{
	UE_LOG(GameInstance, Display, TEXT("Create session %s"), *sessionName.ToString());
}

void UBaseGameInstance::OnJoinSession(const FName Name, EOnJoinSessionCompleteResult::Type ResultJoin)
{
	if (ResultJoin != EOnJoinSessionCompleteResult::Success) return;

	if (SessionInterface && JoinController)
	{
		FDelegateHandle handle = DelegateJoinSessionComplete.GetHandle();
		SessionInterface->ClearOnJoinSessionCompleteDelegate_Handle(handle);

		FString URL;
		SessionInterface->GetResolvedConnectString(SessionName, URL);
		if (!URL.IsEmpty())
		{
			JoinController->ClientTravel(URL, ETravelType::TRAVEL_Absolute);
		}
	}
}

UBaseSaveGame* UBaseGameInstance::GetLoadFromOptionsSlot(int UserIndex)
{
	return Cast<UBaseSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotOptions, UserIndex));
}

UBaseSaveGame* UBaseGameInstance::CreateSaveObject()
{
	return Cast<UBaseSaveGame>(UGameplayStatics::CreateSaveGameObject(UBaseSaveGame::StaticClass()));
}

FString UBaseGameInstance::GetNameSlotOptions() const
{
	return SaveSlotOptions;
}

void UBaseGameInstance::SaveObjectToSlot(UBaseSaveGame* object, int UserIndex)
{
	UGameplayStatics::SaveGameToSlot(object, GetNameSlotOptions(), UserIndex);
}

bool UBaseGameInstance::IsCreateSaveSlot() const
{
	TArray<FString> Files;
	IFileManager::Get().FindFilesRecursive(Files, *FPaths::ProjectSavedDir(), *FString::Printf(TEXT("%s.*"), *SaveSlotOptions), true, false);

	return !Files.IsEmpty();
}
