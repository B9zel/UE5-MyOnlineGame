// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <OnlineSessionSettings.h>
#include "W_SlotSession.generated.h"



class FOnlineSessionSearchResult;

UCLASS()
class MYGAME2_API UW_SlotSession : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UButton* B_Session;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UTextBlock* TB_serverName;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UTextBlock* TB_players;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UTextBlock* TB_Ping;

	UPROPERTY(EditAnywhere)
	FKey MouseButton;
	
private:

	FOnlineSessionSearchResult* SessionInfo;

public:

	void SetSessionSearchInfo(FOnlineSessionSearchResult* SessionSearchInfo);

protected:

	virtual void NativeConstruct() override;

private:

	UFUNCTION()
	void OnPressesSession();
};
