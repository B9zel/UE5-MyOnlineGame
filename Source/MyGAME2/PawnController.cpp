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



UStatisticsMenu* APawnController::CreateTabMenu()
{
	return Cast<UStatisticsMenu>(CreateWidget<UUserWidget>(this,UserWidget));
}

void APawnController::EnableTabMenu()
	{
	if (!HasAuthority())
	{
		TabMenu = CreateTabMenu();
		if (TabMenu != nullptr)
		{
			TabMenu->AddToViewport();
		}
	}
}

void APawnController::DisableTabMenu()
{
	if (TabMenu != nullptr)
	{
		TabMenu->RemoveFromParent();
		TabMenu = nullptr;
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
	if (Game_Interface != nullptr)
	{
		Game_Interface->RemoveFromParent();
		DisableInput(this);
	}
	if (TabMenu == nullptr)
	{
		EnableTabMenu();
	}
	UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(this, TabMenu);
}


void APawnController::Set_RefForWidget_OnClient()
{
	if (!HasAuthority() && isActivateWidget && Game_Interface != nullptr)
	{
		if (!Game_Interface->IsInViewport())
		{
			Game_Interface->AddToViewport();
		}
		else
		{
			Game_Interface->SetVisibility(ESlateVisibility::Visible);
		}
		Cast<ABaseTank>(GetPawn())->Main_Widget = Game_Interface;
	}
	else if (!HasAuthority() && Game_Interface != nullptr)
	{
		Game_Interface->SetVisibility(ESlateVisibility::Collapsed);
		//Game_Interface->Widget_HP->Ref_MainTank = nullptr;
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
