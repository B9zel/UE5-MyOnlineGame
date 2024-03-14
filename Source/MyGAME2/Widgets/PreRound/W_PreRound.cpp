// Fill out your copyright notice in the Description page of Project Settings.


#include "W_PreRound.h"
#include "W_SelectionPawn.h"
#include <Kismet/KismetInputLibrary.h>
#include "../../PawnController.h"


void UW_PreRound::NativeConstruct()
{
	Super::NativeConstruct();

	SetKeyboardFocus();
}

void UW_PreRound::NativeOnFocusLost(const FFocusEvent& InFocusEvent)
{
	Super::NativeOnFocusLost(InFocusEvent);
}

void UW_PreRound::NativeOnFocusChanging(const FWeakWidgetPath& PreviousFocusPath, const FWidgetPath& NewWidgetPath, const FFocusEvent& InFocusEvent)
{
	Super::NativeOnFocusChanging(PreviousFocusPath, NewWidgetPath, InFocusEvent);

	
	if (NewWidgetPath.FindArrangedWidget(W_SelectionPawn->TakeWidget()))
	{
		return;
	}
	if (InFocusEvent.GetCause() != EFocusCause::SetDirectly)
	{
		SetKeyboardFocus();
	}

}

FReply UW_PreRound::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	UUserWidget::NativeOnKeyDown(InGeometry, InKeyEvent);

	if (UKismetInputLibrary::EqualEqual_KeyKey(InKeyEvent.GetKey(), FKey(FName("Escape"))))
	{
		GetOwningPlayer<APawnController>()->SwitchPauseMenu(true);
	}

	return FReply::Handled();
}