
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_Reload.generated.h"




UCLASS()
class MYGAME2_API UWidget_Reload : public UUserWidget
{
	GENERATED_BODY()

public:
	
	//UFUNCTION(BlueprintCallable)
	virtual bool Initialize() override;

	virtual void Construct();

	void Construct_Widget();

	void StartTimer();

	void FinishTimer();
	UFUNCTION()
	void Timer();

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Text;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* SecondsText;
	
	float Seconds;

	FTimerHandle handle;

	class APawnController* OwnerController;

	class ABaseTank* owner;
};
