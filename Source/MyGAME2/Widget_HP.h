
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_HP.generated.h"




UCLASS()
class MYGAME2_API UWidget_HP : public UUserWidget
{
	GENERATED_BODY()

		
public:

	//UFUNCTION(BlueprintCallable)
	virtual bool Initialize() override;

	UFUNCTION()
	ABaseTank* InitailizeRefWidget();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class ABaseTank* Ref_MainTank;

	UFUNCTION()
	void UpdateData();

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UVerticalBox* verticalbox;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UHorizontalBox* horizontal_box;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UProgressBar* progress_bar;

	/*UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* Max_HP;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* CourentHP;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UTextBlock* Slesh;*/
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* HP_TextBlock;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//	TSubclassOf<class ABaseTank> object;

	float percent;
};
