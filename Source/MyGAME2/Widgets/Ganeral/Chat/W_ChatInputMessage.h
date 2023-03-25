// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_ChatInputMessage.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME2_API UW_ChatInputMessage : public UUserWidget
{
	GENERATED_BODY()

private:

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* m_TB_inputMessage;

	UPROPERTY(meta = (BindWidget))
	class UButton* m_B_sendMessage;

protected:

	
	UFUNCTION()
	virtual void NativeConstruct() override;
	UFUNCTION()
	virtual void BindOnTextCommited(const FText& Text, ETextCommit::Type CommitMethod);
	UFUNCTION()
	virtual void BindButtonClick();

public:

	 UEditableTextBox* GetTB_InputMessage() const;
};
