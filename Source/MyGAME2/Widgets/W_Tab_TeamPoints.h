// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_Tab_TeamPoints.generated.h"




UCLASS()
class MYGAME2_API UW_Tab_TeamPoints : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		class UTextBlock* TextPoints;

	class ATeamGameState* Game_State;
	
	UPROPERTY(Editanywhere, BlueprintReadWrite)
	bool isOwnTeam;

	enum E_Team Team;
protected:

	virtual void NativeConstruct() override;
	UFUNCTION()
	FText BindTextPoints();
	//UFUNCTION()
//	FSlateColor BindColor();
};
