
#include "W_FindSessions.h"
#include <Components/Button.h>
#include <Components/ScrollBox.h>
#include <Components/EditableTextBox.h>
#include <Kismet/GameplayStatics.h>
#include <Components/CheckBox.h>
#include "../../Game/BaseGameInstance.h"
#include "W_SlotSession.h"
#include "W_MainMenu.h"


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
}

void UW_FindSessions::ClickRefreshSessions()
{
	if (!IsFindSessions)
	{
		IsFindSessions = true;
	//	Cast<UW_MainMenu>(GetParent()->GetOuter()->GetOuter())->SwitchFindWidget(1);

		TArray<FOnlineSessionSearchResult> Sessions;
		Sessions = Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(this))->findSession(GetOwningPlayer(),CB_LAN->IsChecked());


		for (auto& el : Sessions)
		{
			UW_SlotSession* widget = CreateWidget<UW_SlotSession>(GetOwningPlayer(),SlotSession);
			widget->SessionInfo = &el;
			
			SB_AllSessions->AddChild(widget);
		}


	//	Cast<UW_MainMenu>(GetParent()->GetOuter()->GetOuter())->SwitchFindWidget(0);
		IsFindSessions = false;
	}
}

void UW_FindSessions::ClickConnectToIP()
{
	if (!ED_InoutIP->GetText().IsEmpty())
	{
		Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(this))->joinSession(ED_InoutIP->GetText().ToString(), GetOwningPlayer());
	}
}

UButton* UW_FindSessions::GetButtonConnectToIP()
{
	return B_ConnectToIP;
}
