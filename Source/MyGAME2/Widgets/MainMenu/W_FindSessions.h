// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_FindSessions.generated.h"



UCLASS()
class MYGAME2_API UW_FindSessions : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual bool Initialize() override;
	void NativeConstruct() override;
	UFUNCTION()
	virtual void ClickRefreshSessions();
	UFUNCTION()
	virtual void ClickConnectToIP();

protected:
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UButton* B_RefreshSessions;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		class UButton* B_ConnectToIP;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UScrollBox* SB_AllSessions;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UCheckBox* CB_LAN;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UEditableTextBox* ED_InoutIP;
private:

	bool IsFindSessions;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UW_SlotSession> SlotSession;
};
