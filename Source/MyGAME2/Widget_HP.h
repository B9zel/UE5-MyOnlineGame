
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
		class UCanvasPanel* canves_panel;
	
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UBorder* border;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UVerticalBox* verticalbox;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UHorizontalBox* horizontal_box;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UProgressBar* progress_bar;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UOverlay* overlap;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UHorizontalBox* Horizonta_fromText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* Max_HP;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* CourentHP;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UTextBlock* Slesh;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//	TSubclassOf<class ABaseTank> object;

	float percent;
};
