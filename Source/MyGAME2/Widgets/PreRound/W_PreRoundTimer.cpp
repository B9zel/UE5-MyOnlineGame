
#include "W_PreRoundTimer.h"
#include <Components/TextBlock.h>
#include <MyGAME2/Game/BaseGameState.h>
#include <Kismet/GameplayStatics.h>

void UW_PreRoundTimer::NativeConstruct()
{
	Super::NativeConstruct();

	Timer->TextDelegate.BindDynamic(this, &UW_PreRoundTimer::UpdateTimerTick);
	Timer->SynchronizeProperties();

	Game_State = Cast<ABaseGameState>(UGameplayStatics::GetGameState(this));
}

FText UW_PreRoundTimer::UpdateTimerTick()
{
	if (Game_State->GetPreStartRoundTime().GetMinutes() < 10)
	{
		if (Game_State->GetPreStartRoundTime().GetSeconds() < 10)
		{
			return FText::FromString("0" + FString::FromInt(Game_State->GetPreStartRoundTime().GetMinutes()) + ":" + "0" + FString::FromInt(Game_State->GetPreStartRoundTime().GetSeconds()));
		}
		else
		{
			return FText::FromString("0" + FString::FromInt(Game_State->GetPreStartRoundTime().GetMinutes()) + ":" + FString::FromInt(Game_State->GetPreStartRoundTime().GetSeconds()));
		}
	}
	else
	{
		return FText::AsTimespan(Game_State->GetPreStartRoundTime());
	}
}
