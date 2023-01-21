
#include "ChatComponent.h"
#include <GameFramework/PlayerState.h>
#include <Internationalization/Text.h>


UChatComponent::UChatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


void UChatComponent::BeginPlay()
{
	Super::BeginPlay();

	SetIsReplicated(true);
}


void UChatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UChatComponent::OnPostMessage(const FText& messege, APlayerState* player)
{
	AllSendMessage_Multicast(messege, player);
}

void UChatComponent::AllSendMessage_Multicast_Implementation(const FText& message, class APlayerState* player)
{
	PostMessage.Broadcast(message, player);
}

