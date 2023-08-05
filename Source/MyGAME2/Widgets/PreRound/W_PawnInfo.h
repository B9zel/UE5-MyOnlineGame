// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../Enums/E_AllPawns.h"
#include "Blueprint/UserWidget.h"
#include "W_PawnInfo.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME2_API UW_PawnInfo : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	//class UWidgetSwitcher* WS_Info;
	
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UTextBlock* InfoForPawn;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FText h = FText::FromString("Hello");
	
	UPROPERTY(BlueprintReadWrite)
	TMap<TEnumAsByte<E_AllPawns>, FText> PawnsInfo;

public:
	UFUNCTION(BlueprintCallable)
	void SetSwitchInfo(E_AllPawns E_pawm);


protected:

	virtual void NativeConstruct() override;
	virtual bool Initialize() override;
	UFUNCTION()
	FText GetLightTankInfo();
	UFUNCTION()
	FText GetMediumTankInfo();
	UFUNCTION()
	FText GetStelsTankInfo();
	UFUNCTION()
	FText GetHeavyTankInfo();
};
