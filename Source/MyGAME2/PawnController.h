
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

	void EnableTabMenu();

	void DisableTabMenu();

	void ActivateChatWidget();

	void DeactivateChatWidget();

	void Respawn();
	UFUNCTION()
	void AxisAddPithInput(float Axis);
	UFUNCTION()
		void AxisAddYawInput(float Axis);

	UFUNCTION()
		void OnEscape();

	virtual void SetInputMode(const FInputModeDataBase& InData) override;

	virtual void OnPossess(APawn* pawn) override;
	UFUNCTION(Client, Unreliable)
	void OnPossessClient(APawn* ptrPawn);
protected:
		
	float SensitivityX;
	float SensitivityY;

	

	bool isEnableInput;
public:

	UFUNCTION()
	void RoundEndedInRespawnOnServer();
	
	void TimerRespawn(float Time);
	UFUNCTION(Server, Reliable)
	void SendMessege_OnServer(const FText& messege);
	UFUNCTION(Server, Unreliable)
	void SetSelectedMap(int MapIndex);

	UFUNCTION()
	void SetInputOnUI(bool isEnable,UWidget* widget = nullptr);
	UFUNCTION(Server, Unreliable)
	void SetSpawnPawn(TSubclassOf<class APawn> spawnPawn);

	void SetBlockInput(bool isBlock);
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class APawn> Spawn_Pawn;

	FTimerHandle RespawnTime;
	static enum E_InputMode inputMode;
};

