// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <OnlineSessionSettings.h>
#include "W_SlotSession.generated.h"



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
	
protected:

	virtual void NativeConstruct() override;

	virtual FReply NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
public:

	//UPROPERTY(EditAnywhere)
		class FOnlineSessionSearchResult* SessionInfo;
};
