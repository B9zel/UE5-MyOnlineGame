// Fill out your copyright notice in the Description page of Project Settings.


#include "W_SuperPower.h"
#include <Components/ProgressBar.h>
#include <Components/TextBlock.h>


bool UW_SuperPower::Initialize()
{
	Super::Initialize();
	this->callTime = 0.1f;

	return true;
}

void UW_SuperPower::Activate_Implementation(float InRate)
{
	if (Handle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(Handle);
	}
	this->OffsetPercent = 1.f / (InRate / callTime);
	GetWorld()->GetTimerManager().SetTimer(Handle, this, &UW_SuperPower::TimerUse, callTime, true);
}

void UW_SuperPower::Reload_Implementation(float InRate)
{
	if (Handle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(Handle);
	}
	this->OffsetPercent = 1.f / (InRate / callTime);
	GetWorld()->GetTimerManager().SetTimer(Handle, this, &UW_SuperPower::TimerReload, callTime, true);
}

void UW_SuperPower::TimerReload()
{
	if (PB_reloadSuperSkill->GetPercent() < 1)
	{
		PB_reloadSuperSkill->SetPercent(PB_reloadSuperSkill->GetPercent() + OffsetPercent);
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(Handle);
		Handle.Invalidate();
	}
}

void UW_SuperPower::TimerUse()
{
	if (PB_reloadSuperSkill->GetPercent() > 0)
	{
		PB_reloadSuperSkill->SetPercent(PB_reloadSuperSkill->GetPercent() - OffsetPercent);
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(Handle);
		Handle.Invalidate();
	}
}

