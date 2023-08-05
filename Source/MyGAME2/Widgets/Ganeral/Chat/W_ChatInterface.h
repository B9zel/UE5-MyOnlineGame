// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_ChatInterface.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME2_API UW_ChatInterface : public UUserWidget
{
	GENERATED_BODY()
protected:

	UPROPERTY(meta = (BindWidget))
	class UW_Chat* Chat;

public:

	void Activate();

	void Deactivate();

	bool IsChatActivate() const;
};
