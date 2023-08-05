// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_PauseMenu.generated.h"




UCLASS()
class MYGAME2_API UW_PauseMenu : public UUserWidget
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
		class UButton* B_Play;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		class UWidgetSwitcher* SW_Switch;
public:
	UPROPERTY(meta = (BindWidget))
		class UW_MainMenuOption* W_Options;

	/*UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UVerticalBox* VB_SwitchListSessions;*/

protected:
	UFUNCTION()
		virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
	UFUNCTION()
		virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	UFUNCTION()
		virtual void ClickFindServer();
	UFUNCTION()
		virtual void ClickOptions();
	UFUNCTION()
		virtual void ClickQuitInMenu();
	UFUNCTION()
		virtual void ClickPlay();

public:

	bool isActive;

};
