
#pragma once

#include "CoreMinimal.h"
#include "../../Enums/E_AllPawns.h"
#include "Blueprint/UserWidget.h"
#include "W_PreSelectPawn.generated.h"


class APawnController;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateSelect, E_AllPawns, pawn);

UCLASS()
class MYGAME2_API UW_PreSelectPawn : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget))
	class UButton* B_SelectPawn;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintAssignable)
		FDelegateSelect D_Select;

protected:

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ABaseTank> SelectionPawn;
	UPROPERTY(EditAnywhere)
		TEnumAsByte<E_AllPawns> E_Pawn;

private:

	APawnController* Controller;
	bool HasDisable;
	
protected:

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION()
	virtual void OnClickSelectPawn();
};
