

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
#include "Enums/E_GameState.h"
#include "Game/BaseGameInstance.h"
#include "Game/Save/BaseSaveGame.h"
#include "BaseTank.h"
#include "Game/PlayerStatistic.h"
#include "Widgets/MainMenu/W_MainMenuOption.h"
#include "Widgets/Ganeral/PauseMenu/W_PauseMenu.h"




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
		Game_State->PreRoundStarted.AddDynamic(this, &APawnController::PreRoundStart);
		if (!HasAuthority())
		{
			Game_State->DSpawnSpectator.AddDynamic(this, &APawnController::OnSpawnSpectator);
			Game_State->DSpawnTank.AddDynamic(this, &APawnController::OnSpawnBaseTank);
		}
		
	}
	
	if (HasAuthority())
	{
		Cast<ABase_GameMode>(UGameplayStatics::GetGameMode(this))->RoundEnded.AddDynamic(this, &APawnController::RoundEndedInRespawnOnServer);
		SetReplicates(true);		
	}
	else
	{
		HUD = GetHUD<ABaseHUD>();
		
		UpdateSensetivity();
	}
}

void APawnController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if (InputComponent != nullptr)
	{
		InputComponent->BindAxis("LookUp", this, &APawnController::AxisAddPithInput);
		InputComponent->BindAxis("LookRight", this, &APawnController::AxisAddYawInput);
		InputComponent->BindAction("CreateWidget", IE_Pressed, this, &APawnController::EnableTabMenu);
		InputComponent->BindAction("CreateWidget", IE_Released, this, &APawnController::DisableTabMenu);
		InputComponent->BindAction("SwitchChat", IE_Pressed, this, &APawnController::ActivateChatWidget);
		InputComponent->BindAction("Escape", IE_Pressed, this, &APawnController::OnEscape);
	}
}


void APawnController::OnPossess(APawn* pawn)
{
	APlayerController::OnPossess(pawn);

	OnClientPossess(pawn);
}

void APawnController::OnSpawnBaseTank()
{
}

void APawnController::OnSpawnSpectator()
{
}

void APawnController::OnClientPossess_Implementation(APawn* pawn)
{
}

void APawnController::Respawn()
{
	if (Spawn_Pawn.GetDefaultObject() != nullptr)
	{
		Cast<ABase_GameMode>(UGameplayStatics::GetGameMode(this))->Spawn_Player(this, Spawn_Pawn);
	}
}

void APawnController::AxisAddPithInput(float Axis)
{
	AddPitchInput(Axis * Sensitivity.Y);
}

void APawnController::AxisAddYawInput(float Axis)
{
	AddYawInput(Axis * Sensitivity.X);
}

void APawnController::TimerRespawn(float Time)
{
	RespawnTime.Invalidate();
	GetWorldTimerManager().SetTimer(RespawnTime, this, &APawnController::Respawn, Time);
}

void APawnController::SetInputOnUI(bool isEnable, UWidget* widgetFocus)
{
	if (isEnable && widgetFocus != nullptr)
	{
		SetShowMouseCursor(true);
		FInputModeUIOnly InputMode;
		InputMode.SetWidgetToFocus(widgetFocus->TakeWidget());
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		
		SetInputMode(InputMode); 
	}
	else
	{
		SetShowMouseCursor(false);

		FInputModeGameOnly InputMode;
		InputMode.SetConsumeCaptureMouseDown(true);
		SetInputMode(InputMode);
	}
}

void APawnController::SetBlockInputOnOwningPawn(bool isBlock)
{
	APawn* pawn = GetPawn();
	if (isBlock)
	{
		if (pawn != nullptr)
			pawn->DisableInput(this);
	}
	else
	{
		if (pawn != nullptr)
			pawn->EnableInput(this);
	}
}

void APawnController::UpdateSensetivity()
{
	UBaseSaveGame* saveSlot = Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(this))->GetLoadFromOptionsSlot();
	if (saveSlot != nullptr)
	{
		Sensitivity = saveSlot->Sensetive;
	}
	else
	{
		Sensitivity.X = 1.f;
		Sensitivity.Y = 1.f;
	}
}

void APawnController::BindSensetivity(FVector2D Sensetivity)
{
	this->Sensitivity = Sensetivity;
}


void APawnController::SetSpawnPawn_Implementation(TSubclassOf<class APawn> pawn)
{
	this->Spawn_Pawn = pawn;
}

void APawnController::EnableTabMenu()
{	
	if (HUD != nullptr && !HasAuthority())
	{
		HUD->ToggleTab(true);
		HUD->ToggleSuperPower(false);
		HUD->ToggleHUD(false);
	}
}

void APawnController::DisableTabMenu()
{	
	if (HUD != nullptr && !HasAuthority())
	{
		HUD->ToggleTab(false);
		HUD->ToggleSuperPower(true);
		HUD->ToggleHUD(true);
	}
}

void APawnController::ActivateChatWidget()
{
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
}

void APawnController::RoundStarted()
{
}

void APawnController::PreRoundStart()
{
}

void APawnController::OnEscape()
{
	if (HUD != nullptr)
	{
		if (HUD->isActivateChat())
		{
			DeactivateChatWidget();
		}
		else
		{
			SwitchPauseMenu(!HUD->IsActivatePauseMenu());
		}
	}
}


void APawnController::SwitchPauseMenu(bool isEnable)
{
	if (HUD != nullptr)
	{
		if (isEnable)
		{
			UW_PauseMenu* Widget = HUD->TogglePauseMenu(true);
			if (Widget != nullptr)
				if (!Widget->W_Options->D_OptionSensetivity.Contains(this, "BindSensetivity"))
					Widget->W_Options->D_OptionSensetivity.AddDynamic(this, &APawnController::BindSensetivity);
		}
		else
		{
			HUD->TogglePauseMenu(false);
		}
	}
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
