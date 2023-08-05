// Fill out your copyright notice in the Description page of Project Settings.


#include "W_ResultsEndRound.h"
#include <Components/Border.h>
#include <Components/TextBlock.h>
#include <MyGAME2/Game/BaseHUD.h>
#include <MyGAME2/Widgets/StatisticsMenu.h>
#include <MyGAME2/Game/PlayerStatistic.h>
#include <Kismet/GameplayStatics.h>
#include <MyGAME2/Game/BaseGameState.h>
#include "W_EndRoundMapVote.h"
#include <Kismet/KismetInputLibrary.h>
#include "../../PawnController.h"



void UW_ResultsEndRound::NativeConstruct()
{
	InitializeTabResults();
	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle, this, &UW_ResultsEndRound::InitializeTextResult, 0.6f, false);

}

void UW_ResultsEndRound::InitializeTabResults()
{
	B_ResultsRound->AddChild(CreateWidget(GetOwningPlayer(), GetOwningPlayer()->GetHUD<ABaseHUD>()->TabWidgetClass));
}

void UW_ResultsEndRound::InitializeTextResult()
{
	APlayerState* L_playerStat = GetOwningPlayer()->GetPlayerState<APlayerState>();
	for (auto& el : UGameplayStatics::GetGameState(this)->PlayerArray)
	{
		if (Cast<APlayerStatistic>(el)->Kills > Cast<APlayerStatistic>(L_playerStat)->Kills)
		{
			L_playerStat = el;
		}
	}

	if (GetOwningPlayer()->PlayerState == L_playerStat)
	{
		T_Winner->SetText(FText::FromString(FString("Victory with " + FString::FromInt(Cast<APlayerStatistic>(L_playerStat)->Kills) + " kills")));
		FLinearColor color = FLinearColor(0.f, 0.f, 1.f, 1.f); //Blue color
		T_Winner->SetColorAndOpacity(FSlateColor(color));
	}
	else
	{
		T_Winner->SetText(FText::FromString("Defeat"));
		FLinearColor color = FLinearColor(1.f, 0.f, 0.f, 1.f); // Red color
		T_Winner->SetColorAndOpacity(FSlateColor(color));
	}

}

FReply UW_ResultsEndRound::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	UUserWidget::NativeOnKeyDown(InGeometry, InKeyEvent);

	if (UKismetInputLibrary::EqualEqual_KeyKey(InKeyEvent.GetKey(), FKey(FName("Escape"))))
	{
		GetOwningPlayer<APawnController>()->SwitchPauseMenu(true);
	}

	return FReply::Handled();
}
