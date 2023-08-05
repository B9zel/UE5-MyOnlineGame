// Fill out your copyright notice in the Description page of Project Settings.


#include "W_ChatInterface.h"
#include "W_Chat.h"



void UW_ChatInterface::Activate()
{
	SetVisibility(ESlateVisibility::Visible);

	Chat->ActivateChat();
}

void UW_ChatInterface::Deactivate()
{
	SetVisibility(ESlateVisibility::Collapsed);

	Chat->DeactivateChat();
}

bool UW_ChatInterface::IsChatActivate() const
{
	return Chat->isActivate;
}
