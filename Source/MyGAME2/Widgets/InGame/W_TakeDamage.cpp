// Fill out your copyright notice in the Description page of Project Settings.


#include "W_TakeDamage.h"
#include <Components/TextBlock.h>
#include <Kismet/GameplayStatics.h>
#include "../../Game/BaseHUD.h"


void UW_TakeDamage::NativeConstruct()
{
	Super::NativeConstruct();

	T_Damage->SetText(FText::FromString(FString::FromInt(Damage)));
}

void UW_TakeDamage::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (GetOwningPlayer() != nullptr)
	{
		FVector2D ScreenPosition;
		UGameplayStatics::ProjectWorldToScreen(GetOwningPlayer(), WorldLocation, ScreenPosition);

		SetPositionInViewport(ScreenPosition);
	}
}

void UW_TakeDamage::RemoveWidget()
{
	ABaseHUD* HUD = GetOwningPlayer()->GetHUD<ABaseHUD>();
	if (HUD != nullptr)
		HUD->ToggleTakeDamage(false);
}
