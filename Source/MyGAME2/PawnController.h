
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PawnController.generated.h"



UCLASS()
class MYGAME2_API APawnController : public APlayerController
{
	GENERATED_BODY()

public:
	APawnController();
	
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;
	
	virtual void SetupInputComponent() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	UFUNCTION()
	void RoundEnded();

	void Respawn();

	void TimerRespawn(float Time);

	UFUNCTION()
		UStatisticsMenu* CreateTabMenu();

	void EnableTabMenu();

	void DisableTabMenu();

	void Set_GameWidget(class UGame_Interface* Widget);
	
	UFUNCTION()
	void Set_RefForWidget_OnClient();

public:

	UPROPERTY(ReplicatedUsing = Set_RefForWidget_OnClient)
	bool isActivateWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class APawn> Spawn_Pawn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UGame_Interface* Game_Interface;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStatisticsMenu* TabMenu;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> UserWidget;
};
