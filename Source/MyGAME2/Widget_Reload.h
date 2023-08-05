
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

	void Construct_Widget(float Time, float Rate,float Step);
	void DestructWidget();
private:
	void StartTimer(float Rate);

	void FinishTimer();
	UFUNCTION()
	void Timer();

public:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Text;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* SecondsText;
	
private:
	float m_Time;
	float m_Step;
	FTimerHandle m_handle;

	class ABaseTank* owner;
};
