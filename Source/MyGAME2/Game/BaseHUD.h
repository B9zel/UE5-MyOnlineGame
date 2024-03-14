
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

	class UW_Spectator* ToggleSpectatorHUD(bool isShow);

	class UW_PreRound* TogglePreRound(bool isShow);

	class UW_ResultsEndRound* ToggleEndRound(bool isShow);

	void CreateAimWidget();

	void RemoveAimWidget();

	void ToggleChat(bool isActivate);

	class UW_SuperPower* ToggleSuperPower(bool isShow, bool isRemove = false);

	void ToggleAim(bool isShow);

	class UW_PauseMenu* TogglePauseMenu(bool isShow);

	class UW_Waiting* ToggleWaitingMenu(bool isShow);

	class UW_TakeDamage* ToggleTakeDamage(bool isShow,float Damage = 0,const FVector& WorldPosition = FVector(0));

	void ActivateReload(float Time, float Rate, float Step);

	void DeactivateReload();

	bool isActivateChat();

	bool IsActivatePauseMenu();

	void SetWidgetSuperPower(class UW_SuperPower* Widget);
	
	UFUNCTION()
	const UGame_Interface* GetHUDWidget() const;
	UFUNCTION()
	const UStatisticsMenu* GetTabWidget() const;
	UFUNCTION()
	const UW_ChatInterface* GetChatWidget() const;
	UFUNCTION()
	void ActivateSuperSkillWidget(float InRate);
	UFUNCTION()
	void ReloadSuperSkillWidget(float InRate);
	UFUNCTION()
		void StartReload(float Time,float Rate,float Step);
	UFUNCTION()
		void FinishReload();

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
		TSubclassOf<class UW_ChatInterface> ChatWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UW_Aim> AimWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UW_PauseMenu> PauseMenuWidgetClass;
	UPROPERTY()
		TSubclassOf<class UW_SuperPower> superskillWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UW_Waiting> WaitingWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UW_TakeDamage> TakeDamageWidgetClass;
	
private:

	class UStatisticsMenu* m_TabWidget;
	class UGame_Interface* m_HUDWidget;
	class UW_Spectator* m_SpectatorWidget;
	class UW_PreRound* m_PreRoundWidget;
	class UW_ResultsEndRound* m_EndRoundWidget;
	class UW_ChatInterface* m_ChatWidget;
	class UW_SuperPower* m_superskillWidget;
	class UW_Aim* m_aimWidget;
	class UW_PauseMenu* m_PauseMenuWidget;
	class UW_Waiting* m_WaitingWidget;
	class UW_TakeDamage* m_TakeDamageWidget;
	
	bool isActivatePauseMenu;
private:

	class UW_ChatInterface* CreateChat();
};
