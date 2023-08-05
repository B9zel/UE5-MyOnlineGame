
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PawnController.generated.h"




UCLASS()
class MYGAME2_API APawnController : public APlayerController
{
	GENERATED_BODY()

protected:
	
	APawnController();

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	UFUNCTION()
	void RoundEndedOnClient();
	UFUNCTION()
	void RoundStarted();
	UFUNCTION()
	void PreRoundStart();

	void EnableTabMenu();

	void DisableTabMenu();

	void ActivateChatWidget();

	void DeactivateChatWidget();

	void Respawn();

	void SetBlockInputOnOwningPawn(bool isBlock);

	void UpdateSensetivity();
	UFUNCTION()
	void BindSensetivity(FVector2D Sensetivity);

	UFUNCTION()
	void AxisAddPithInput(float Axis);
	UFUNCTION()
		void AxisAddYawInput(float Axis);

	UFUNCTION()
		void OnEscape();

	virtual void OnPossess(APawn* pawn) override;

	UFUNCTION(Client, Unreliable)
		void OnClientPossess(APawn* p_pawn);
	
	UFUNCTION()
	void OnSpawnBaseTank();
	UFUNCTION()
	void OnSpawnSpectator();

protected:
		
	FVector2D Sensitivity;

	class ABaseHUD* HUD;
public:

	UFUNCTION()
	void RoundEndedInRespawnOnServer();
	
	void TimerRespawn(float Time);
	UFUNCTION(Server, Reliable)
	void SendMessege_OnServer(const FText& messege);
	UFUNCTION(Server, Unreliable)
	void SetSelectedMap(int MapIndex);
	UFUNCTION()
	void SwitchPauseMenu(bool isEnable);

	UFUNCTION()
	void SetInputOnUI(bool isEnable,UWidget* widget = nullptr);
	UFUNCTION(Server, Unreliable)
	void SetSpawnPawn(TSubclassOf<class APawn> spawnPawn);

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class APawn> Spawn_Pawn;

	FTimerHandle RespawnTime;
	static enum E_InputMode inputMode;
};

