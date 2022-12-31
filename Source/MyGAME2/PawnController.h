
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

	virtual void SetupInputComponent() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	UFUNCTION()
	void RoundEndedOnClient();
	UFUNCTION()
	void RoundStarted();

	void Respawn();

	void TimerRespawn(float Time);

	void EnableTabMenu();

	void DisableTabMenu();

	UFUNCTION()
	void RoundEndedInRespawnOnServer();
	//UFUNCTION()
	

public:


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class APawn> Spawn_Pawn;

	FTimerHandle RespswnTime;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//class UGame_Interface* Game_Interface;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	class UStatisticsMenu* TabMenu;
};
