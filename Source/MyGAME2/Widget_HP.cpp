
#include "Widget_HP.h"
#include <Components/CanvasPanel.h>
#include <Components/Border.h>
#include <Components/VerticalBox.h>
#include <Components/HorizontalBox.h>
#include <Components/ProgressBar.h>
#include <Components/Overlay.h>
#include <Components/TextBlock.h>
#include "Heads_Stats.h"
#include <MyGAME2/BaseTank.h>




ABaseTank* UWidget_HP::InitailizeRefWidget()
{
	return Cast<ABaseTank>(GetOwningPlayerPawn());
}


bool UWidget_HP::Initialize()
{
	Super::Initialize();

	Ref_MainTank = InitailizeRefWidget();
	
	if (Ref_MainTank != nullptr)
	{
		UpdateData();
		return true;
	}
	return false;
}


void UWidget_HP::UpdateData()
{
	if (Ref_MainTank != GetOwningPlayerPawn())
	{
		Ref_MainTank = InitailizeRefWidget();
	}

	Max_HP->SetText(FText::FromString(FString::FromInt(Ref_MainTank->component->Max_HP)));
	CourentHP->SetText(FText::FromString(FString::FromInt(Ref_MainTank->component->Courrent_HP)));
	
	percent = Ref_MainTank->component->Courrent_HP / Ref_MainTank->component->Max_HP;//(Ref_MainTank->component->Courrent_HP / (Ref_MainTank->component->Max_HP / 100.0f));
	//percent /= 100.0f;

	progress_bar->SetPercent(percent);

	if (percent <= 0.2f && Ref_MainTank->component->Courrent_HP != 0.0f)
	{
		progress_bar->SetFillColorAndOpacity(FLinearColor::Red);
	}
}

//void UWidget_HP::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
//{
//	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
//	
//	DOREPLIFETIME(UWidget_HP,Ref_MainTank)
//}
