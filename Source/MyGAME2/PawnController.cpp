

#include <MyGAME2/PawnController.h>
#include <Blueprint/WidgetBlueprintLibrary.h>
#include <Kismet/GameplayStatics.h>
#include <MyGAME2/Game/Base_GameMode.h>
#include <Net/UnrealNetwork.h>
#include <MyGAME2/Game/BaseGameState.h>
#include <MyGAME2/Widgets/StatisticsMenu.h>
#include <MyGAME2/Game/BaseHUD.h>
#include <MyGAME2/Game_Spectator.h>
#include <MyGAME2/Game/Components/ChatComponent.h>
#include <GameFramework/PlayerState.h>
#include "Widgets/Ganeral/Chat/W_Chat.h"
#include "Game/Components/VoteComponent.h"





APawnController::APawnController()
{
	
}

void APawnController::BeginPlay()
{
	Super::BeginPlay();

	ABaseGameState* Game_State = Cast<ABaseGameState>(UGameplayStatics::GetGameState(this));
	if (Game_State != nullptr)
	{
		Game_State->RoundEnded.AddDynamic(this, &APawnController::RoundEndedOnClient);
		Game_State->RoundStarted.AddDynamic(this, &APawnController::RoundStarted);
	}
	if (HasAuthority())
	{
		Cast<ABase_GameMode>(UGameplayStatics::GetGameMode(this))->RoundEnded.AddDynamic(this, &APawnController::RoundEndedInRespawnOnServer);
		SetReplicates(true);
	}
	
}

void APawnController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if (InputComponent != nullptr)
	{
		InputComponent->BindAxis("LookUp", this, &APawnController::AddPitchInput);
		InputComponent->BindAxis("LookRight", this, &APawnController::AddYawInput);
		InputComponent->BindAction("CreateWidget",IE_Pressed, this, &APawnController::EnableTabMenu);
		InputComponent->BindAction("CreateWidget", IE_Released, this, &APawnController::DisableTabMenu);
		InputComponent->BindAction("SwitchChat", IE_Pressed, this, &APawnController::ActivateChatWidget);
		InputComponent->BindAction("Escape", IE_Pressed, this, &APawnController::DeactivateChatWidget);
	}
}

void APawnController::Respawn()
{
	if (Spawn_Pawn.GetDefaultObject() != nullptr)
	{
		Cast<ABase_GameMode>(UGameplayStatics::GetGameMode(this))->Spawn_Player(this, Spawn_Pawn);
	}
}

void APawnController::TimerRespawn(float Time)
{
	RespawnTime.Invalidate();
	GetWorldTimerManager().SetTimer(RespawnTime, this, &APawnController::Respawn, Time);
}

void APawnController::SetInputOnUI(bool isEnable, UWidget* widget)
{
	if (isEnable)
	{
		bShowMouseCursor = true;
		FInputModeUIOnly InputMode;
		InputMode.SetWidgetToFocus(widget->TakeWidget());
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

		SetInputMode(InputMode);
	}
	else
	{
		bShowMouseCursor = false;
		
		FInputModeGameOnly InputMode;
		SetInputMode(InputMode);
	}
}

void APawnController::EnableTabMenu()
{
	ABaseHUD* HUD = GetHUD<ABaseHUD>();
	if (HUD != nullptr && !HasAuthority())
	{
		HUD->ToggleTab(true);
		HUD->ToggleSuperPower(false);
		HUD->ToggleHUD(false);
	}
}

void APawnController::DisableTabMenu()
{
	ABaseHUD* HUD = GetHUD<ABaseHUD>();
	if (HUD != nullptr && !HasAuthority())
	{
		HUD->ToggleTab(false);
		HUD->ToggleSuperPower(true);
		HUD->ToggleHUD(true);
	}
}

void APawnController::ActivateChatWidget()
{
	ABaseHUD* HUD = GetHUD<ABaseHUD>();
	if (HUD != nullptr)
	{
		if (!HUD->isActivateChat())
		{
			HUD->ToggleChat(true);
		}
	}
}

void APawnController::DeactivateChatWidget()
{
	ABaseHUD* HUD = GetHUD<ABaseHUD>();
	if (HUD != nullptr)
	{
		if (HUD->isActivateChat())
		{
			HUD->ToggleChat(false);
		}
	}
}


void APawnController::RoundEndedInRespawnOnServer()
{
	Cast<ABase_GameMode>(UGameplayStatics::GetGameMode(this))->RoundEnded.RemoveDynamic(this, &APawnController::RoundEndedInRespawnOnServer);
	GetWorldTimerManager().ClearTimer(RespawnTime);
}

void APawnController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void APawnController::RoundEndedOnClient()
{

	//DisableInput(this);
}

void APawnController::RoundStarted()
{
}


void APawnController::SendMessege_OnServer_Implementation(const FText& messege)
{
	Cast<ABaseGameState>(UGameplayStatics::GetGameState(this))->chatComponent->OnPostMessage(messege, GetPlayerState<APlayerState>());
}


void APawnController::SetSelectedMap_Implementation(int MapIndex)
{
	Cast<ABaseGameState>(UGameplayStatics::GetGameState(this))->voteComponent->SetVote(GetPlayerState<APlayerState>(), MapIndex);
}


//void APawnController::Set_RefForWidget_OnClient()
//{
//	ABaseHUD* HUD = Cast<ABaseHUD>(GetHUD());
//	if (!HasAuthority())
//	{
//		if (HUD != nullptr)
//		{
//			HUD->ToggleHUD(true);
//		}
//		Cast<ABaseTank>(GetPawn())->Main_Widget = HUD->GetHUDWidget();
//	}
//	else if (!HasAuthority())
//	{
//		if (HUD != nullptr)
//		{
//			HUD->ToggleHUD(false);
//		}
//	}
//}

//APawnController::APawnController(const FObjectInitializer& ObjectInitializer)
//{
	//static ConstructorHelpers::FClassFinder<UUserWidget> MainMenuwidget(TEXT("/Game/UI/BP_GameInterface"));
	//
	//if (!ensure(MainMenuwidget.Class != nullptr)) //|| !ensure(widgetHP.Class !=nullptr
	//{
	//	
	//	return;
	//}
	//MainMenuWidgetclass = MainMenuwidget.Class;	
//}
