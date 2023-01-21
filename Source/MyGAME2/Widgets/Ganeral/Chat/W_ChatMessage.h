// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_ChatMessage.generated.h"



UCLASS()
class MYGAME2_API UW_ChatMessage : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;

protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* T_PlayerName;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* T_Message;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* T_Time;
public:
	UPROPERTY(BlueprintReadWrite)
	FText message;
	UPROPERTY(BlueprintReadWrite)
	class APlayerState* player;
private:

	FText GetTime();
};
