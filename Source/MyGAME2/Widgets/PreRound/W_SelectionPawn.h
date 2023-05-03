// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../Enums/E_AllPawns.h"
#include "Blueprint/UserWidget.h"
#include "W_SelectionPawn.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME2_API UW_SelectionPawn : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget),BlueprintReadWrite)
	class UW_PreSelectPawn* W_HeavyTank;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UW_PreSelectPawn* W_LightTank;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UW_PreSelectPawn* W_MediumTank;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UW_PreSelectPawn* W_StelsTank;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UW_PawnInfo* W_Info;

protected:

	virtual void NativeConstruct() override;
	UFUNCTION()
	virtual void OnSelectedPawn(E_AllPawns pawn);
};
