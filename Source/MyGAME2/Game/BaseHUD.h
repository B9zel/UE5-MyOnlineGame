
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

	void ToggleChat(bool isActivate);

	void ToggleSuperPower(bool isShow, bool isRemove = false);

	void ToggleAim(bool isShow);

	bool isActivateChat();

	UFUNCTION()
	void OnSpawnTankPawn(TSubclassOf<UW_SuperPower> Widget);

	void SetWidgetSuperPower(class UW_SuperPower* Widget);
	
	UFUNCTION()
	const UGame_Interface* GetHUDWidget() const;
	UFUNCTION()
	const UStatisticsMenu* GetTabWidget() const;
	UFUNCTION()
	const UW_Chat* GetChatWidget() const;
	UFUNCTION()
	void ActivateSuperSkillWidget(float InRate);
	UFUNCTION()
	void ReloadSuperSkillWidget(float InRate);

protected:
	UFUNCTION()
		void OnRoundStarted();
	UFUNCTION()
		void OnRoundEnded();

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UW_Chat> ChatWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UW_Aim> AimWidgetClass;
	UPROPERTY()
		TSubclassOf<class UW_SuperPower> superskillWidgetClass;
	
private:

	class UStatisticsMenu* m_TabWidget;
	class UGame_Interface* m_HUDWidget;
	class UW_Spectator* m_SpectatorWidget;
	class UW_PreRound* m_PreRoundWidget;
	class UW_ResultsEndRound* m_EndRoundWidget;
	class UW_Chat* m_ChatWidget;
	class UW_SuperPower* m_superskillWidget;
	class UW_Aim* m_aimWidget;
private:

	void CreateChat();

	
};
