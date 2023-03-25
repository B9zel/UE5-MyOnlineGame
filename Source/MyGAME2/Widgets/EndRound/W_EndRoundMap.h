
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_EndRoundMap.generated.h"



UCLASS()
class MYGAME2_API UW_EndRoundMap : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TB_NumberVotes;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TB_NameMap;
	UPROPERTY(meta = (BindWidget))
	class UButton* B_Select;
	UPROPERTY(meta = (BindWidget))
	class UBorder* B_Icon;
	

public:
	int IndexMap;
	FName NameMap;
protected:

	virtual bool Initialize() override;
	virtual void NativeConstruct() override;

	UFUNCTION()
	virtual void OnClickButton();
	UFUNCTION()
	virtual FText OnTextBind();
private:

	
};
