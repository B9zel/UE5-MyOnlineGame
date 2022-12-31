
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BaseHUD.generated.h"



UCLASS()
class MYGAME2_API ABaseHUD : public AHUD
{
	GENERATED_BODY()
	
public:

	~ABaseHUD();

	virtual void BeginPlay() override;

	void ToggleHUD(bool isShow);

	void ToggleTab(bool isShow);

	void ToggleSpectatorHUD(bool isShow);

	void TogglePreRound(bool isShow);

	void ToggleEndRound(bool isShow);
	UFUNCTION()
	void OnRoundStarted();

	UFUNCTION()
		void OnRoundEnded();

	UFUNCTION()
	UGame_Interface* GetHUDWidget();
	UFUNCTION()
	UStatisticsMenu* GetTabWidget();

	UFUNCTION()
	void OnPlayerAlive();
	UFUNCTION()
	void OnPlayerDead(ABaseTank* DeathInstigator);
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UStatisticsMenu> TabWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UGame_Interface> HUDWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UW_Spectator> SpectatorWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UW_PreRound> PreRoundWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UW_ResultsEndRound> EndRoundWidgetClass;
private:

	class UStatisticsMenu* m_TabWidget;
	class UGame_Interface* m_HUDWidget;
	class UW_Spectator* m_SpectatorWidget;
	class UW_PreRound* m_PreRoundWidget;
	class UW_ResultsEndRound* m_EndRoundWidget;
};
