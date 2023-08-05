
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
	
	return true;
}

void UWidget_Reload::Construct()
{
	Super::Construct();
	
}

void UWidget_Reload::Construct_Widget(float Time, float Rate,float Step)
{	
	m_Time = Time;
	m_Step = Step;

	SecondsText->SetText(FText::FromString(FString::SanitizeFloat(m_Time)));//UKismetTextLibrary::Conv_FloatToText(Seconds, TEnumAsByte<ERoundingMode>::EnumType::HalfToEven, false, true, 1, 324, 1, 2)
	SetVisibility(ESlateVisibility::Visible);

	StartTimer(Rate);
}

void UWidget_Reload::DestructWidget()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

void UWidget_Reload::StartTimer(float Rate)
{
	GetWorld()->GetTimerManager().SetTimer(m_handle, this, &UWidget_Reload::Timer, Rate, true);
}

void UWidget_Reload::FinishTimer()
{
	GetWorld()->GetTimerManager().PauseTimer(m_handle);
}


void UWidget_Reload::Timer()
{
	m_Time -= m_Step;
	if (m_Time < 0.0f)
	{
		m_Time = 0.0f;
	}
	SecondsText->SetText(FText::FromString(FString::SanitizeFloat(m_Time)));
	
}
