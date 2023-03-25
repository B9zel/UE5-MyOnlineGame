
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PawnController.generated.h"



UCLASS()
class MYGAME2_API APawnController : public APlayerController
{
	GENERATED_BODY()

private:
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
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class APawn> Spawn_Pawn;

	FTimerHandle RespawnTime;
};
