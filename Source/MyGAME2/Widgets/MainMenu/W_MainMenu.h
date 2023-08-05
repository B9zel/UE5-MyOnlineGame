// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_MainMenu.generated.h"




UCLASS()
class MYGAME2_API UW_MainMenu : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UButton* B_FindServer;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UButton* B_Options;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UButton* B_Quit;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UWidgetSwitcher* SW_Switch;
	UPROPERTY(meta = (BindWidget))
	class UW_MainMenuOption* W_Options;
	UPROPERTY(meta = (BindWidget))
	class UW_FindSessions* W_FindSession;
	
	/*UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UVerticalBox* VB_SwitchListSessions;*/

protected:

	virtual bool Initialize() override;
	UFUNCTION()
	virtual void NativeConstruct() override;
	UFUNCTION()
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	UFUNCTION()
	virtual void ClickFindServer();
	UFUNCTION()
	virtual void ClickOptions();
	UFUNCTION()
	virtual void ClickQuit();

	UFUNCTION()
	virtual void OnChangeNickName(FText NickName);
};
