// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu_widget.generated.h"




UCLASS()
class MYGAME2_API UMainMenu_widget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

	/*UFUNCTION()
	void Clicked_HostButton();
	UFUNCTION()
	void Clicked_JoinButton();
	UFUNCTION()
	void Clicked_ExitButton();
	UFUNCTION()
	void Text_changed(const FText& Text);*/

	UPROPERTY(meta = (BindWidget))
		class UCanvasPanel* canvas_panel;

	UPROPERTY(meta = (BindWidget))
		class USizeBox* sizebox;

	UPROPERTY(meta = (BindWidget))
		class UButton* HostButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* JoinButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* ExitButton;


	

	

};
