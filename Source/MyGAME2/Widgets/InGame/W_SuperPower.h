// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_SuperPower.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME2_API UW_SuperPower : public UUserWidget
{
	GENERATED_BODY()


protected:

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		class UProgressBar* PB_reloadSuperSkill;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		class UTextBlock* T_keyPress;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float callTime;

	double OffsetPercent;

	FTimerHandle Handle;
public:
	UFUNCTION(BlueprintNativeEvent)
	void Activate(float InRate);
	UFUNCTION(BlueprintNativeEvent)
	void Reload(float InRate);

protected:

	virtual bool Initialize() override;
	
	virtual void TimerReload();
	
	virtual void TimerUse();
};
