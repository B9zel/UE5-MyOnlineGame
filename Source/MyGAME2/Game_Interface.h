// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Game_Interface.generated.h"


/**
 * 
 */
UCLASS()
class MYGAME2_API UGame_Interface : public UUserWidget
{
	GENERATED_BODY()

	//virtual bool Initialize() override;

public:
	
	UFUNCTION(BlueprintCallable)
		void Take_Ref(class ABaseTank* pawn);

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* canvasPanel;

	UPROPERTY(meta = (BindWidget))
	class UWidget_HP* HeadsStats;

	UPROPERTY(meta = (BindWidget))
	class UWidget_Reload* ReloadStats;
	UPROPERTY(meta = (BindWidget))
	class UW_RoundTime* Timer;
};
