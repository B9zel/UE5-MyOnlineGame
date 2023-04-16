
#include "Widget_Reload.h"
#include <Components/CanvasPanel.h>
#include <Components/TextBlock.h>
#include <Components/Border.h>
#include <Kismet/KismetTextLibrary.h>
#include <Kismet/KismetStringLibrary.h>
#include "BaseTank.h"
#include "PawnController.h"
#include "Game_Interface.h"




bool UWidget_Reload::Initialize()
{
	Super::Initialize();
	OwnerController = Cast<APawnController>(GetOwningPlayer());
	
	return true;
}

void UWidget_Reload::Construct()
{
	Super::Construct();
	
}

void UWidget_Reload::Construct_Widget()
{
	if (owner == nullptr)
	{
		owner = Cast<ABaseTank>(GetOwningPlayerPawn());
	}
	
	Seconds = owner->GetTimeReload();
	
	SecondsText->SetText(FText::FromString(FString::SanitizeFloat(Seconds))); //UKismetTextLibrary::Conv_FloatToText(Seconds, TEnumAsByte<ERoundingMode>::EnumType::HalfToEven, false, true, 1, 324, 1, 2)
	SetVisibility(ESlateVisibility::Visible);
	StartTimer();
	
}

void UWidget_Reload::StartTimer()
{
	GetWorld()->GetTimerManager().SetTimer(handle, this, &UWidget_Reload::Timer, 0.1f, true);
}

void UWidget_Reload::FinishTimer()
{
	SetVisibility(ESlateVisibility::Collapsed);
	GetWorld()->GetTimerManager().PauseTimer(handle);
}


void UWidget_Reload::Timer()
{
	Seconds -= 0.1f;
	if (Seconds < 0.0f)
	{
		Seconds = 0.0f;
	}
	SecondsText->SetText(FText::FromString(FString::SanitizeFloat(Seconds)));
	
}
