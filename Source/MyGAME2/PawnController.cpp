// Fill out your copyright notice in the Description page of Project Settings.


#include <MyGAME2/PawnController.h>
#include <Blueprint/WidgetBlueprintLibrary.h>
#include <GameFramework/HUD.h>
#include <Kismet/GameplayStatics.h>
#include <MyGAME2/Game/Base_GameMode.h>
#include <MyGAME2/Game_Interface.h>
#include "BaseTank.h"
#include <Net/UnrealNetwork.h>
#include "Widget_HP.h"
#include <MyGAME2/Game/BaseGameState.h>
#include <MyGAME2/Widgets/StatisticsMenu.h>
#include <Blueprint/WidgetBlueprintLibrary.h>
#include <MyGAME2/Game/BaseHUD.h>


APawnController::APawnController()
{
	SetReplicates(true);

	Game_Interface = nullptr;

	isActivateWidget = false;
}

void APawnController::BeginPlay()
{
	Super::BeginPlay();
	ABaseGameState* Game_State = Cast<ABaseGameState>(UGameplayStatics::GetGameState(this));
	if (Game_State != nullptr)
	{
		Game_State->RoundEnded.AddDynamic(this, &APawnController::RoundEnded);
		Game_State->RoundStarted.AddDynamic(this, &APawnController::RoundStarted);
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
	FTimerHandle Handle;
	GetWorldTimerManager().SetTimer(Handle, this, &APawnController::Respawn, Time);
}


void APawnController::EnableTabMenu()
{
	ABaseHUD* HUD = Cast<ABaseHUD>(GetHUD());
	if (HUD != nullptr)
	{
		HUD->ToggleTab(true);
		HUD->ToggleHUD(false);
	}
}

void APawnController::DisableTabMenu()
{
	ABaseHUD* HUD = Cast<ABaseHUD>(GetHUD());
	if (HUD != nullptr)
	{
		HUD->ToggleTab(false);
		HUD->ToggleHUD(true);
	}
}

void APawnController::Set_GameWidget(UGame_Interface* Widget)
{
	Game_Interface = Widget;
	if (GetPawn() != nullptr)
	{
		Cast<ABaseTank>(GetPawn())->Main_Widget = Widget;
	}
}

void APawnController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ABaseTank* pawn = Cast<ABaseTank>(InPawn);

	if (pawn != nullptr)
	{
		if (pawn->component != nullptr)
		{
			isActivateWidget = true;
		}
	}
}




void APawnController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(APawnController, isActivateWidget, COND_OwnerOnly);
}

void APawnController::RoundEnded()
{
	ABaseHUD* HUD = Cast<ABaseHUD>(GetHUD());
	if (HUD != nullptr)
	{
		HUD->ToggleHUD(false);
		DisableInput(this);
	}
}

void APawnController::RoundStarted()
{
	ABaseHUD* HUD = Cast<ABaseHUD>(GetHUD());
	if (HUD != nullptr)
	{
		HUD->ToggleHUD(true);
	}
}


void APawnController::Set_RefForWidget_OnClient()
{
	ABaseHUD* HUD = Cast<ABaseHUD>(GetHUD());
	if (!HasAuthority() && isActivateWidget)
	{
		if (HUD != nullptr)
		{
			HUD->ToggleHUD(true);
		}
		Cast<ABaseTank>(GetPawn())->Main_Widget = HUD->GetHUDWidget();
	}
	else if (!HasAuthority())
	{
		if (HUD != nullptr)
		{
			HUD->ToggleHUD(false);
		}
	}
}

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
