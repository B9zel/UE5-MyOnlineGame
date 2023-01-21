// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ChatComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FChatDelegate, FText, Message,class APlayerState*, Player);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYGAME2_API UChatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UChatComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FChatDelegate PostMessage;

protected:

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
public:

	UFUNCTION(NetMulticast, Reliable)
	void AllSendMessage_Multicast(const FText& message, class APlayerState* player);
	UFUNCTION()
	void OnPostMessage(const FText& messege, class APlayerState* player);

};
