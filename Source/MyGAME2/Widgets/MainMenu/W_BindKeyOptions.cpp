// Fill out your copyright notice in the Description page of Project Settings.


#include "W_BindKeyOptions.h"
#include <Components/InputKeySelector.h>
#include <Components/TextBlock.h>





void UW_BindKeyOptions::NativeConstruct()
{
	Super::NativeConstruct();

	IKS_ForwardMove->OnIsSelectingKeyChanged.AddDynamic(this, &UW_BindKeyOptions::OnIsSelectingKeyForwardMove);
	IKS_BackMove->OnIsSelectingKeyChanged.AddDynamic(this, &UW_BindKeyOptions::OnIsSelectingKeyBackMove);
	IKS_RightRotation->OnIsSelectingKeyChanged.AddDynamic(this, &UW_BindKeyOptions::OnIsSelectingKeyRightRotation);
	IKS_LeftRotation->OnIsSelectingKeyChanged.AddDynamic(this, &UW_BindKeyOptions::OnIsSelectingKeyLeftRotation);
	IKS_Aiming->OnIsSelectingKeyChanged.AddDynamic(this, &UW_BindKeyOptions::OnIsSelectingKeyAiming);
	IKS_Shoot->OnIsSelectingKeyChanged.AddDynamic(this, &UW_BindKeyOptions::OnIsSelectingKeyShoot);
	IKS_UseSuperPower->OnIsSelectingKeyChanged.AddDynamic(this, &UW_BindKeyOptions::OnIsSelectingKeyUseSuperPower);
	IKS_Chat->OnIsSelectingKeyChanged.AddDynamic(this, &UW_BindKeyOptions::OnIsSelectingKeyChat);
	IKS_StatisticMenu->OnIsSelectingKeyChanged.AddDynamic(this, &UW_BindKeyOptions::OnIsSelectingKeyStatisticMenu);;
	
	//IKSSetOpacity(IKS_ForwardMove, 0);
//	IKSSetOpacity(IKS_BackMove, 0);
	//IKSSetOpacity(IKS_RightRotation, 0);
	//IKSSetOpacity(IKS_LeftRotation, 0);
	//IKSSetOpacity(IKS_Aiming, 0);
	//IKSSetOpacity(IKS_Shoot, 0);
	//IKSSetOpacity(IKS_UseSuperPower, 0);
	//IKSSetOpacity(IKS_Chat, 0);
	//IKSSetOpacity(IKS_StatisticMenu, 0);
}

void UW_BindKeyOptions::ChangingKey(const UInputKeySelector* IK_Selctor,  UTextBlock* T_Input)
{
	if (IK_Selctor->GetIsSelectingKey())
	{
		IKSSetOpacity(IK_Selctor, 1);
		T_Input->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		IKSSetOpacity(IK_Selctor, 0);

		T_Input->SetVisibility(ESlateVisibility::Visible);
	}
}

//void UW_BindKeyOptions::IKSSetOpacity(const UInputKeySelector* IK_selector, float Opacity)
//{
//	FTextBlockStyle TextStyle;
//	TextStyle = IK_selector->GetTextStyle();
//	FLinearColor color = TextStyle.ColorAndOpacity.GetSpecifiedColor();
//
//	color.A = Opacity;
//	TextStyle.SetColorAndOpacity(color);
//}


void UW_BindKeyOptions::SetNoTextForwardMove(const FText Text)
{
	T_ForwardMove->SetText(Text);
}

void UW_BindKeyOptions::SetNoTextBackMove(const FText Text)
{
	T_BackMove->SetText(Text);
}

void UW_BindKeyOptions::SetNoTextRightRotation(const FText Text)
{
	T_RightRotation->SetText(Text);
}

void UW_BindKeyOptions::SetNoTextLeftRotation(const FText Text)
{
	T_LeftRotation->SetText(Text);
}

void UW_BindKeyOptions::SetNoTextAiming(const FText Text)
{
	T_Aiming->SetText(Text);
}

void UW_BindKeyOptions::SetNoTextShoot(const FText Text)
{
	T_Shoot->SetText(Text);
}

void UW_BindKeyOptions::SetNoTextUseSuperPower(const FText Text)
{
	T_UseSuperPower->SetText(Text);
}

void UW_BindKeyOptions::SetNoTextChat(const FText Text)
{
	T_Chat->SetText(Text);
}

void UW_BindKeyOptions::SetNoTextStatisticMenu(const FText Text)
{
	T_StatisticMenu->SetText(Text);
}

void UW_BindKeyOptions::OnIsSelectingKeyForwardMove()
{
	ChangingKey(IKS_ForwardMove, T_ForwardMove);
}

void UW_BindKeyOptions::OnIsSelectingKeyBackMove()
{
	ChangingKey(IKS_BackMove, T_BackMove);
}

void UW_BindKeyOptions::OnIsSelectingKeyRightRotation()
{
	ChangingKey(IKS_RightRotation, T_RightRotation);
}

void UW_BindKeyOptions::OnIsSelectingKeyLeftRotation()
{
	ChangingKey(IKS_LeftRotation, T_LeftRotation);
}

void UW_BindKeyOptions::OnIsSelectingKeyAiming()
{
	ChangingKey(IKS_Aiming, T_Aiming);
}

void UW_BindKeyOptions::OnIsSelectingKeyShoot()
{
	ChangingKey(IKS_Shoot, T_Shoot);
}

void UW_BindKeyOptions::OnIsSelectingKeyUseSuperPower()
{
	ChangingKey(IKS_UseSuperPower, T_UseSuperPower);
}

void UW_BindKeyOptions::OnIsSelectingKeyChat()
{
	ChangingKey(IKS_Chat, T_Chat);
}

void UW_BindKeyOptions::OnIsSelectingKeyStatisticMenu()
{
	ChangingKey(IKS_StatisticMenu, T_StatisticMenu);
}
