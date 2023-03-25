
#include "Widget_HP.h"
#include <Blueprint/UserWidget.h>
#include <Components/CanvasPanel.h>
#include <Components/Border.h>
#include <Components/VerticalBox.h>
#include <Components/HorizontalBox.h>
#include <Components/ProgressBar.h>
#include <Components/Overlay.h>
#include <Components/TextBlock.h>
#include "HealthStat.h"
#include <MyGAME2/BaseTank.h>
#include <Components/Button.h>




ABaseTank* UWidget_HP::InitailizeRefWidget()
{
	return Cast<ABaseTank>(GetOwningPlayerPawn());
}


bool UWidget_HP::Initialize()
{
	Super::Initialize();
	
	Ref_MainTank = InitailizeRefWidget();
	percent = 1.0f;
	//if (Ref_MainTank != nullptr)
	//{
	//	UpdateData();
	//	return true;
	//}
	return false;
}

void UWidget_HP::NativeTick(const FGeometry& MyGeometry, float DelatTime)
{
	Super::NativeTick(MyGeometry, DelatTime);

	UpdateData();
}




void UWidget_HP::UpdateData()
{
	if (Ref_MainTank == nullptr)
	{
		Ref_MainTank = InitailizeRefWidget();
	}
	else
	{
		HP_TextBlock->SetText(FText::FromString(FString::FromInt(Ref_MainTank->HP_Component->Courrent_HP) + " | " + FString::FromInt(Ref_MainTank->HP_Component->Max_HP)));

		percent = Ref_MainTank->HP_Component->Courrent_HP / Ref_MainTank->HP_Component->Max_HP;
		progress_bar->SetPercent(FMath::FInterpTo(progress_bar->GetPercent(), percent, GetWorld()->GetDeltaSeconds(), 7));

		if (percent <= 0.2f && Ref_MainTank->HP_Component->Courrent_HP != 0.0f)
		{
			progress_bar->SetFillColorAndOpacity(FLinearColor::Red);
		}
	}
}

//void UWidget_HP::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
//{
//	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
//	
//	DOREPLIFETIME(UWidget_HP,Ref_MainTank)
//}
