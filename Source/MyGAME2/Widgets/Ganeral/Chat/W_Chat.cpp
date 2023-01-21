
#include "W_Chat.h"
#include <Components/ScrollBox.h>
#include <Components/EditableTextBox.h>
#include <Components/Border.h>
#include <MyGAME2/Game/BaseGameState.h>
#include <Kismet/GameplayStatics.h>
#include <MyGAME2/Game/Components/ChatComponent.h>
#include <MyGAME2/Widgets/Ganeral/Chat/W_ChatMessage.h>
#include <MyGAME2/Widgets/Ganeral/Chat/W_ChatInputMessage.h>



void UW_Chat::NativeConstruct()
{
	Super::NativeConstruct();

	activityTime = 5.0f;

	isActivate = false;
	ABaseGameState* gameState = Cast<ABaseGameState>(UGameplayStatics::GetGameState(this));
	if (gameState != nullptr)
	{
		gameState->chatComponent->PostMessage.AddDynamic(this, &UW_Chat::TakeMessage);
	}
}

void UW_Chat::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	SB_scrolMessage->SetScrollOffset(SB_scrolMessage->GetScrollOffset() + (20 * InDeltaTime));
}

void UW_Chat::TakeMessage(FText message, APlayerState* player)
{
	SetVisibility(ESlateVisibility::Visible);

	UW_ChatMessage* chatMessageWidget = CreateWidget<UW_ChatMessage>(GetOwningPlayer(), W_Message);
	chatMessageWidget->message = message;
	chatMessageWidget->player = player;
	SB_scrolMessage->AddChild(chatMessageWidget);
	
	SetTimerActivity(activityTime);
}

UW_ChatInputMessage* UW_Chat::GetInputMessage() const
{
	return InputMessage;
}

void UW_Chat::ActivateChat()
{
	isActivate = true;
	if (sleepingTimer.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(sleepingTimer);
	}

	SetVisibility(ESlateVisibility::Visible);
	InputMessage->SetVisibility(ESlateVisibility::Visible);
	InputMessage->GetTB_InputMessage()->SetKeyboardFocus();

	B_Chat->SetBrushColor(FLinearColor(0.f, 0.f, 0.f, 0.8f));
}
	

void UW_Chat::DeactivateChat()
{
	isActivate = false;
	InputMessage->SetVisibility(ESlateVisibility::Collapsed);
	B_Chat->SetBrushColor(FLinearColor(0.f, 0.f, 0.f, 0.0f));

	SetTimerActivity(activityTime);
}


void UW_Chat::ActivateSleepingChat()
{
	SetVisibility(ESlateVisibility::Collapsed);
	sleepingTimer.Invalidate();
}

void UW_Chat::SetTimerActivity(float inRate)
{
	if (sleepingTimer.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(sleepingTimer);
	}
	GetWorld()->GetTimerManager().SetTimer(sleepingTimer, this, &UW_Chat::ActivateSleepingChat, inRate, false);
}
