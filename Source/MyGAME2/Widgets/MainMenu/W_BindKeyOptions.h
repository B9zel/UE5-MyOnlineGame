// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_BindKeyOptions.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME2_API UW_BindKeyOptions : public UUserWidget
{
	GENERATED_BODY()
protected:

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UInputKeySelector* IKS_ForwardMove;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UInputKeySelector* IKS_BackMove;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UInputKeySelector* IKS_RightRotation;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UInputKeySelector* IKS_LeftRotation;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UInputKeySelector* IKS_Aiming;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UInputKeySelector* IKS_Shoot;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UInputKeySelector* IKS_UseSuperPower;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UInputKeySelector* IKS_Chat;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UInputKeySelector* IKS_StatisticMenu;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UTextBlock* T_ForwardMove;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UTextBlock* T_BackMove;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UTextBlock* T_RightRotation;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UTextBlock* T_LeftRotation;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UTextBlock* T_Aiming;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UTextBlock* T_Shoot;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UTextBlock* T_UseSuperPower;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UTextBlock* T_Chat;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UTextBlock* T_StatisticMenu;
protected:
	UFUNCTION(BlueprintCallable)
	void SetNoTextForwardMove(const FText Text);
	UFUNCTION(BlueprintCallable)
	void SetNoTextBackMove(const FText Text);
	UFUNCTION(BlueprintCallable)
	void SetNoTextRightRotation(const FText Text);
	UFUNCTION(BlueprintCallable)
	void SetNoTextLeftRotation(const FText Text);
	UFUNCTION(BlueprintCallable)
	void SetNoTextAiming(const FText Text);
	UFUNCTION(BlueprintCallable)
	void SetNoTextShoot(const FText Text);
	UFUNCTION(BlueprintCallable)
	void SetNoTextUseSuperPower(const FText Text);
	UFUNCTION(BlueprintCallable)
	void SetNoTextChat(const FText Text);
	UFUNCTION(BlueprintCallable)
	void SetNoTextStatisticMenu(const FText Text);

	UFUNCTION()
	void OnIsSelectingKeyForwardMove();
	UFUNCTION()
	void OnIsSelectingKeyBackMove();
	UFUNCTION()
	void OnIsSelectingKeyRightRotation();
	UFUNCTION()
	void OnIsSelectingKeyLeftRotation();
	UFUNCTION()
	void OnIsSelectingKeyAiming();
	UFUNCTION()
	void OnIsSelectingKeyShoot();
	UFUNCTION()
	void OnIsSelectingKeyUseSuperPower();
	UFUNCTION()
	void OnIsSelectingKeyChat();
	UFUNCTION()
	void OnIsSelectingKeyStatisticMenu();
	UFUNCTION(BlueprintImplementableEvent)
	void IKSSetOpacity(const UInputKeySelector* IK_selector, float Opacity);

	virtual void NativeConstruct() override;
private:

	void ChangingKey(const UInputKeySelector* IK_Selctor,UTextBlock* T_Input);

	
};
