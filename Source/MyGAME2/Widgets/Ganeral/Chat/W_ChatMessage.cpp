
#include "W_ChatMessage.h"
#include <Components/TextBlock.h>
#include <GameFramework/PlayerState.h>
#include <Kismet/KismetMathLibrary.h>

void UW_ChatMessage::NativeConstruct()
{
	Super::NativeConstruct();

	T_Message->SetText(message);
	T_PlayerName->SetText(FText::FromString("["+player->GetPlayerName()+"]"));
	T_Time->SetText(GetTime());

}



FText UW_ChatMessage::GetTime()
{
	FDateTime dataTime = UKismetMathLibrary::Now();
	FText time = FText::FromString(FString::FromInt(dataTime.GetHour()));
	if (dataTime.GetMinute() < 10)
	{
		time = FText::FromString(time.ToString() + ":0" + FString::FromInt(dataTime.GetMinute()));
	}
	else
	{
		time = FText::FromString(time.ToString() + ":" + FString::FromInt(dataTime.GetMinute()));
	}
	if (dataTime.GetSecond() < 10)
	{
		time = FText::FromString(time.ToString() + ":0" + FString::FromInt(dataTime.GetSecond()));
	}
	else
	{
		time = FText::FromString(time.ToString() + ":" + FString::FromInt(dataTime.GetSecond()));
	}
	return time;
}