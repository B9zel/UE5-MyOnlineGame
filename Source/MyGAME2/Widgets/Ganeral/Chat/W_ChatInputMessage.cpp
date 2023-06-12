// Fill out your copyright notice in the Description page of Project Settings.


#include "W_ChatInputMessage.h"
#include <Components/EditableTextBox.h>
#include <Components/Button.h>
#include <MyGAME2/PawnController.h>
#include <MyGAME2/Game/BaseHUD.h>





void UW_ChatInputMessage::NativeConstruct()
{
	Super::NativeConstruct();

	m_TB_inputMessage->SetRevertTextOnEscape(false);
	m_TB_inputMessage->OnTextCommitted.AddDynamic(this, &UW_ChatInputMessage::BindOnTextCommited);

	m_B_sendMessage->OnClicked.AddDynamic(this, &UW_ChatInputMessage::BindButtonClick);



}

void UW_ChatInputMessage::BindOnTextCommited(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (!m_TB_inputMessage->GetText().IsEmpty() && CommitMethod == ETextCommit::Type::OnEnter)
	{
		GetOwningPlayer<APawnController>()->SendMessege_OnServer(Text);
		m_TB_inputMessage->SetText(FText());
		GetOwningPlayer()->GetHUD<ABaseHUD>()->ToggleChat(false);

	}
	if (CommitMethod == ETextCommit::Type::OnCleared)
	{
		GetOwningPlayer()->GetHUD<ABaseHUD>()->ToggleChat(false); 
		m_TB_inputMessage->SetText(FText());
	}
}

void UW_ChatInputMessage::BindButtonClick()
{
	if (!m_TB_inputMessage->GetText().IsEmpty())
	{
		GetOwningPlayer<APawnController>()->SendMessege_OnServer(m_TB_inputMessage->GetText());
		m_TB_inputMessage->SetText(FText());
	}
}

UEditableTextBox* UW_ChatInputMessage::GetTB_InputMessage() const
{
	return m_TB_inputMessage;
}
