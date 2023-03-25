
#include "W_EndRoundMapVote.h"
#include <Components/ScrollBox.h>
#include "../../Game/BaseGameState.h"
#include <Kismet/GameplayStatics.h>
#include "../../Game/Components/VoteComponent.h"
#include "W_EndRoundMap.h"



void UW_EndRoundMapVote::NativeConstruct()
{
	Super::NativeConstruct();
	Cast<ABaseGameState>(UGameplayStatics::GetGameState(this))->voteComponent->OnCreateToVoteMap.AddDynamic(this, &UW_EndRoundMapVote::CreateToVoteMap);
}

void UW_EndRoundMapVote::CreateToVoteMap(TArray<FName> MapNames)
{
	SB_Maps->ClearChildren();

	for (int i = 0; i < MapNames.Num(); i++)
	{
		UW_EndRoundMap* Widget = CreateWidget<UW_EndRoundMap>(GetOwningPlayer(), EndRoundMapWidget);
		Widget->IndexMap = i;
		Widget->NameMap = MapNames[i];

		SB_Maps->AddChild(Widget);
	}
}
