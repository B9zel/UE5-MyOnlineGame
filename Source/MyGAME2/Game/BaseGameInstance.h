// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "Game_Instance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include <Engine/GameInstance.h>
#include "BaseGameInstance.generated.h"



UCLASS()
class MYGAME2_API UBaseGameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:
	UBaseGameInstance();

	IOnlineSessionPtr SessionInterface;
	TSharedPtr<FOnlineSessionSearch> SessionSearch;
	
public:
	FString SaveSlotOptions;
	
public:

	virtual void joinSession(FOnlineSessionSearchResult& Session, APlayerController* controller);
	void joinSession(FString IP, APlayerController* controller);
	virtual TArray<FOnlineSessionSearchResult> findSession(APlayerController* controller,bool LAN);
};
