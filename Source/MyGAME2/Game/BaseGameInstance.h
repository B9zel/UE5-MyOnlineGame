// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <OnlineSessionSettings.h>
#include <Interfaces/OnlineSessionInterface.h>

#include <Engine/GameInstance.h>
#include "BaseGameInstance.generated.h"



class IOnlineSubsystem;
class FOnlineSessionSearchResult;
namespace EOnJoinSessionCompleteResult
{
	enum Type;
}


DECLARE_MULTICAST_DELEGATE_OneParam(FOneParamDelegate, TArray<FOnlineSessionSearchResult>&);
DECLARE_MULTICAST_DELEGATE(FWithoutParamDelegate);


UCLASS()
class MYGAME2_API UBaseGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UBaseGameInstance();

public:

	virtual void joinSession(FOnlineSessionSearchResult& Session, APlayerController* controller);
	void joinSession(FString IP, APlayerController* controller);
	void findSession(APlayerController* controller, bool LAN);

	UFUNCTION(BlueprintCallable)
	class UBaseSaveGame* GetLoadFromOptionsSlot(int UserIndex = 0);
	UFUNCTION(BlueprintCallable)
	class UBaseSaveGame* CreateSaveObject();

	FString GetNameSlotOptions() const;
	UFUNCTION(BlueprintCallable)
	void SaveObjectToSlot(UBaseSaveGame* object, int UserIndex = 0);
	UFUNCTION(BlueprintPure)
	bool IsCreateSaveSlot() const;

protected:

	virtual void Init() override;
	void CreateSession();

private:

	UFUNCTION()
	void OnFindSessionComplete(bool IsWasFound);
	UFUNCTION()
	void OnCancelFindSession(bool IsCancel);
	UFUNCTION()
	void OnCreateSession(FName sessionName, bool IsCreate);
	//UFUNCTION()
	void OnJoinSession(const FName Name, EOnJoinSessionCompleteResult::Type ResultJoin);

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<enum E_PlayerSpace> PlayerSpace;

	FOneParamDelegate FindSessionCompleteDelegate;
	FWithoutParamDelegate CancelFindSessionCompleteDelegate;

protected:

	TSharedPtr<FOnlineSessionSearch> SessionSearch;

	class UBaseSaveGame* SaveObject;
	FString SaveSlotOptions;

private:

	IOnlineSubsystem* SubSystem;
	IOnlineSessionPtr SessionInterface;

	FOnFindSessionsCompleteDelegate DelegateFindSesssionComplete;
	FOnCancelFindSessionsCompleteDelegate DelegateCancelSessionComplete;
	FOnCreateSessionCompleteDelegate DelegateCreateSessionComplete;
	FOnJoinSessionCompleteDelegate DelegateJoinSessionComplete;

	APlayerController* JoinController;
	FOnlineSessionSearchResult* JoinSession;

	FName SessionName;
};
