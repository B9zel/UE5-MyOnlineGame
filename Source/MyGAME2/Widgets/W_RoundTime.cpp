
#include "W_RoundTime.h"
#include <Components/TextBlock.h>
#include <MyGAME2/Game/BaseGameState.h>
#include <Kismet/GameplayStatics.h>


void UW_RoundTime::NativeConstruct()
{
	Super::NativeConstruct();
	
	Timer->TextDelegate.BindDynamic(this, &UW_RoundTime::UpdateTimerTick);
	Timer->SynchronizeProperties();
	
	Game_State = Cast<ABaseGameState>(UGameplayStatics::GetGameState(this));
}

FText UW_RoundTime::UpdateTimerTick()
{
	if (Game_State->RoundTime.GetMinutes() < 10)
	{
		if (Game_State->RoundTime.GetSeconds() < 10)
		{
			return FText::FromString("0" + FString::FromInt(Game_State->RoundTime.GetMinutes()) + ":" + "0" + FString::FromInt(Game_State->RoundTime.GetSeconds()));
		}
		else
		{
			return FText::FromString("0" + FString::FromInt(Game_State->RoundTime.GetMinutes()) + ":" + FString::FromInt(Game_State->RoundTime.GetSeconds()));
		}
	}
	else
	{
		return FText::AsTimespan(Game_State->RoundTime);
	}
}