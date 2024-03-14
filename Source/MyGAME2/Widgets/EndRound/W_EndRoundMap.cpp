// Fill out your copyright notice in the Description page of Project Settings.


#include "W_EndRoundMap.h"
#include <Components/TextBlock.h>
#include <Components/Button.h>
#include "../../PawnController.h"
#include <Kismet/GameplayStatics.h>
#include "../../Game/BaseGameState.h"
#include "../../Game/Components/VoteComponent.h"
#include <Engine/DataTable.h>
#include <Kismet/DataTableFunctionLibrary.h>
#include "../../Data/ST_MapInfo.h"
#include <Kismet/GameplayStatics.h>
#include <Components/Border.h>


bool UW_EndRoundMap::Initialize()
{
	Super::Initialize();
	
	TB_NumberVotes->TextDelegate.BindDynamic(this, &UW_EndRoundMap::OnTextBind);
	
	return true;
}

void UW_EndRoundMap::NativeConstruct()
{
	Super::NativeConstruct();

	UDataTable* dataTable = Cast<ABaseGameState>(UGameplayStatics::GetGameState(this))->voteComponent->DataTable;
	FST_MapInfo* MapInfo = dataTable->FindRow<FST_MapInfo>(NameMap, "");
	
	if (MapInfo != nullptr)
	{
		B_Icon->SetBrushFromTexture(MapInfo->Icon);
		TB_NameMap->SetText(MapInfo->ShowNameMap);
	}
	B_Select->OnClicked.AddDynamic(this, &UW_EndRoundMap::OnClickButton);
	B_Select->SynchronizeProperties();
	TB_NumberVotes->SynchronizeProperties();
}

void UW_EndRoundMap::OnClickButton()
{
	GetOwningPlayer<APawnController>()->SetSelectedMap(IndexMap);
}

FText UW_EndRoundMap::OnTextBind()
{
	int Vote = Cast<ABaseGameState>(UGameplayStatics::GetGameState(this))->voteComponent->GetMapVote(IndexMap);
	return FText::FromString(FString::FromInt(Vote));
}

