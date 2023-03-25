// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_Chat.generated.h"



UCLASS()
class MYGAME2_API UW_Chat : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(meta = (BindWidget),BlueprintReadWrite)
	class UScrollBox* SB_scrolMessage;
	UPROPERTY(meta = (BindWidget))
	class UW_ChatInputMessage* InputMessage;
	UPROPERTY(meta = (BindWidget))
	class UBorder* B_Chat;

	FTimerHandle sleepingTimer;

public:

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UW_ChatMessage> W_Message;

	bool isActivate;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float activityTime;

protected: 

	UFUNCTION()
		virtual bool Initialize() override;
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION()
	virtual void TakeMessage(FText message, APlayerState* player);

	void ActivateSleepingChat();

	void SetTimerActivity(float inRate);

	UFUNCTION()
	void OnEndRound();

public:

	UW_ChatInputMessage* GetInputMessage() const;

	void ActivateChat();

	void DeactivateChat();
};
