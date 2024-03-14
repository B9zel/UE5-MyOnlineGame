// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../Enums/E_AllPawns.h"
#include "Blueprint/UserWidget.h"
#include "W_PawnInfo.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME2_API UW_PawnInfo : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	//class UWidgetSwitcher* WS_Info;
	
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UTextBlock* InfoForPawn;
	
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<TEnumAsByte<E_AllPawns>, FText> PawnsInfo;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	 FText TextHeavyTank = NSLOCTEXT("PreRound","K_HeavyTank", "Heavy tank");
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	 FText TextLightTank = NSLOCTEXT("PreRound", "K_LightTank", "Light tank"); 
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	 FText TextMediumTank = NSLOCTEXT("PreRound", "K_MediumTank", "Medium tank"); 
	 UPROPERTY(BlueprintReadOnly, EditAnywhere)
	 FText TextStealthTank = NSLOCTEXT("PreRound", "K_StealthTank", "Stealth tank");


	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	 FText TextSpeedTank = NSLOCTEXT("PreRound", "K_Speed", "Speed: ");

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	 FText TextRotationSpeedTank = NSLOCTEXT("PreRound", "K_RotationSpeed", "Rotation speed: ");
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	 FText TextTowerRotationSpeedTank = NSLOCTEXT("PreRound", "K_TowerRotationSpeed", "Tower rotation speed: ");

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	 FText TextDamageTank = NSLOCTEXT("PreRound", "K_Damage", "Damage: ");
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	 FText TextHPTank = NSLOCTEXT("PreRound", "K_HP", "Health points(HP): ");

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	 FText TextTimeReloadTank = NSLOCTEXT("PreRound", "K_TimeReload", "Time reload: ");

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	 FText TextSkillLightTank = NSLOCTEXT("PreRound", "K_SkillLightTank", "Skill: Up tank speed");
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	 FText TextSkillHeavyTank = NSLOCTEXT("PreRound", "K_SkillHeavyTank", "Skill: Next attack with up damage");
	 UPROPERTY(BlueprintReadOnly, EditAnywhere)
	 FText TextSkillMediumTank = NSLOCTEXT("PreRound", "K_SkillMediumTank", "Skill: Immunity to attacks");
	 UPROPERTY(BlueprintReadOnly, EditAnywhere)
	 FText TextSkillStealthTank = NSLOCTEXT("PreRound", "K_SkillStealthTank", "Skill: Invisibility");

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FText TextSkillTimeReloadTank = NSLOCTEXT("PreRound", "K_SkillTimeReload", "Skill time reload: ");
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	 FText TextSkillTimeUseTank = NSLOCTEXT("PreRound", "K_SkillTimeUse", "Skill time use: ");
	 UPROPERTY(BlueprintReadOnly, EditAnywhere)
	 FText TextSeconds = NSLOCTEXT("PreRound", "K_Seconds", " seconds"); 

public:
	UFUNCTION(BlueprintCallable)
	void SetSwitchInfo(E_AllPawns E_pawm);


protected:

	virtual void NativeConstruct() override;
	virtual bool Initialize() override;
	UFUNCTION()
	FText GetLightTankInfo();
	UFUNCTION()
	FText GetMediumTankInfo();
	UFUNCTION()
	FText GetStealthTankInfo();
	UFUNCTION()
	FText GetHeavyTankInfo();

	UFUNCTION()
	FText GetRULightTankInfo();
	UFUNCTION()
	FText GetRUMediumTankInfo();
	UFUNCTION()
	FText GetRUStealthTankInfo();
	UFUNCTION()
	FText GetRUHeavyTankInfo();
};
