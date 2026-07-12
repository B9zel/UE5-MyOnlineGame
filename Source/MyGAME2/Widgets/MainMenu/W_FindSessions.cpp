
#include "W_FindSessions.h"
#include <Components/Button.h>
#include <Components/ScrollBox.h>
#include <Components/EditableTextBox.h>
#include <Kismet/GameplayStatics.h>
#include <Components/CheckBox.h>
#include "../../Game/BaseGameInstance.h"
#include "W_SlotSession.h"
#include "W_MainMenu.h"



DECLARE_LOG_CATEGORY_CLASS(WidgetFindSession, All, All);




bool UW_FindSessions::Initialize()
{
	Super::Initialize();

	IsFindSessions = false;

	return true;
}

void UW_FindSessions::NativeConstruct()
{
	Super::NativeConstruct();

	B_RefreshSessions->OnClicked.AddDynamic(this, &UW_FindSessions::ClickRefreshSessions);
	B_ConnectToIP->OnClicked.AddDynamic(this, &UW_FindSessions::ClickConnectToIP);

	GetWorld()->GetGameInstance<UBaseGameInstance>()->FindSessionCompleteDelegate.Add(TDelegate<void(TArray<FOnlineSessionSearchResult>&), FDefaultDelegateUserPolicy>::CreateUObject(this, &UW_FindSessions::OnFindSessionComplete));
	GetWorld()->GetGameInstance<UBaseGameInstance>()->CancelFindSessionCompleteDelegate.AddLambda([this]() {

		IsFindSessions = false;

		});
}

void UW_FindSessions::ClickRefreshSessions()
{
	UE_LOG(WidgetFindSession, Display, TEXT("Is Find session: %d"), IsFindSessions);
	if (!IsFindSessions)
	{
		IsFindSessions = true;
	//	Cast<UW_MainMenu>(GetParent()->GetOuter()->GetOuter())->SwitchFindWidget(1);

		TArray<FOnlineSessionSearchResult> Sessions;
		Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(this))->findSession(GetOwningPlayer(),CB_LAN->IsChecked());
	}
}

void UW_FindSessions::ClickConnectToIP()
{
	if (!ED_InoutIP->GetText().IsEmpty())
	{
		Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(this))->joinSession(ED_InoutIP->GetText().ToString(), GetOwningPlayer());
	}
}

void UW_FindSessions::OnFindSessionComplete(TArray<FOnlineSessionSearchResult>& SessionFound)
{
	UE_LOG(WidgetFindSession, Display, TEXT("FindSession Complete. Num: %d"), SessionFound.Num());
	SB_AllSessions->ClearChildren();
	for (auto& el : SessionFound)
	{
		UW_SlotSession* widget = CreateWidget<UW_SlotSession>(GetOwningPlayer(), SlotSession);
		widget->SetSessionSearchInfo(&el);

		SB_AllSessions->AddChild(widget);
	}

	IsFindSessions = false;
}

UButton* UW_FindSessions::GetButtonConnectToIP()
{
	return B_ConnectToIP;
}
