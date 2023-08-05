// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_TakeDamage.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME2_API UW_TakeDamage : public UUserWidget
{
	GENERATED_BODY()
protected:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* T_Damage;
public:
	float Damage;
	FVector	WorldLocation;

protected:

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	UFUNCTION(BlueprintCallable)
	void RemoveWidget();
};
