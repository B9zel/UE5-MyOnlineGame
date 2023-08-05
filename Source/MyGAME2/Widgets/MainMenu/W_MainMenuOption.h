// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_MainMenuOption.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDispatchOptionOneParam, FVector2D, sensitivity);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDispathOptionOneParamFText, FText, NickName);

UCLASS()
class MYGAME2_API UW_MainMenuOption : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta = (BindWidget))
		class UButton* B_Windowed;
	UPROPERTY(meta = (BindWidget))
		class UButton* B_BorderlessWindow;
	UPROPERTY(meta = (BindWidget))
		class UButton* B_FullScreen;
	UPROPERTY(meta = (BindWidget))
		class UButton* B_Auto;
	UPROPERTY(meta = (BindWidget))
		class UButton* B_Apply;
	UPROPERTY(meta = (BindWidget))
		class UButton* B_Reset;

	UPROPERTY(meta = (BindWidget))
		class UComboBoxString* CB_Resolution;
	UPROPERTY(meta = (BindWidget))
		class UComboBoxString* CB_Shadow;
	UPROPERTY(meta = (BindWidget))
		class UComboBoxString* CB_VisualEffect;
	UPROPERTY(meta = (BindWidget))
		class UComboBoxString* CB_ViewDistance;
	UPROPERTY(meta = (BindWidget))
		class UComboBoxString* CB_Texture;
	UPROPERTY(meta = (BindWidget))
		class UComboBoxString* CB_Shading;
	UPROPERTY(meta = (BindWidget))
		class UComboBoxString* CB_Reflection;
	UPROPERTY(meta = (BindWidget))
		class UComboBoxString* CB_AntiAliasing;
	UPROPERTY(meta = (BindWidget))
		class UComboBoxString* CB_PostProcessing;

	UPROPERTY(meta = (BindWidget))
		class USlider* S_ResolutionScale;
	UPROPERTY(meta = (BindWidget))
		class USlider* S_SensetiveX;
	UPROPERTY(meta = (BindWidget))
		class USlider* S_SensetiveY;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* T_PercentResolutionScale;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* T_PercentSensetivityX;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* T_PercentSensetivityY;
	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* ET_Nickname;

public:
	FDispatchOptionOneParam D_OptionSensetivity;
	FDispathOptionOneParamFText D_ChangeNickName;
protected:


	virtual void NativeConstruct() override;

	virtual bool Initialize() override;

	

	void UpdateInfo();

	void UpdateButtonsDisplayMode();
	void UpdateCurrentResolutionInfo();
	void UpdateResolutionScaleQuality();
	void UpdateShadowQuality();
	void UpdateVisualEffectQuality();
	void UpdateViewDistanceQuality();
	void UpdateTextureQuality();
	void UpdateShadingQuality();
	void UpdateRefflectionQuality();
	void UpdateAntiAliasingQuality();
	void UpdatePostProcessingQuality();
	void UpdateSensetivity();
	void UpdateNickname();

	UFUNCTION()
	FText OnBindPercentResolutionScale();
	UFUNCTION()
		FText OnBindPercentSensetivityX();
	UFUNCTION()
		FText OnBindPercentSensetivityY();

	UFUNCTION()
		virtual void OnClickWindowedButton();
	UFUNCTION()
		virtual void OnClickBorderlessWindowButton();
	UFUNCTION()
		virtual void OnClickFullScreenButton();
	UFUNCTION()
		virtual void OnClickAutoButton();
	UFUNCTION()
		virtual void OnClickApplyButton();
	UFUNCTION()
		virtual void OnResetChanges();
	

	UFUNCTION()
	virtual void OnSelectResolution(FString SelectedItem, ESelectInfo::Type SelectionType);
	UFUNCTION()
	virtual void OnSelectAntiAliasing(FString SelectedItem, ESelectInfo::Type SelectionType);
	UFUNCTION()
		virtual void OnSelectViewDistance(FString SelectedItem, ESelectInfo::Type SelectionType);
	UFUNCTION()
		virtual void OnSelectVisualEffect(FString SelectedItem, ESelectInfo::Type SelectionType);
	UFUNCTION()
		virtual void OnSelectShadow(FString SelectedItem, ESelectInfo::Type SelectionType);
	UFUNCTION()
		virtual void OnSelectTexture(FString SelectedItem, ESelectInfo::Type SelectionType);
	UFUNCTION()
		virtual void OnSelectShading(FString SelectedItem, ESelectInfo::Type SelectionType);
	UFUNCTION()
		virtual void OnSelectReflection(FString SelectedItem, ESelectInfo::Type SelectionType);
	UFUNCTION()
		virtual void OnSelectPostProcessing(FString SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION()
		virtual void OnChangeValue(float Value);
	UFUNCTION()
		virtual void OnSensetivityXChanges(float Value);
	UFUNCTION()
		virtual void OnSensetivityYChanges(float Value);
	UFUNCTION()
	virtual void OnCommitedText(const FText& Text, ETextCommit::Type CommitMethod);

	void SaveToObjectSensetivity(class UBaseSaveGame* const SaveObject, const FVector2D SavedSensetivityInSlot,const FVector2D Sens);
	void SaveToObjectNickname(class UBaseSaveGame* const SaveObject, const FText SavedNickInSlot, const FText Nickname);

private:

	class UGameUserSettings* UserSettings;

	FVector2D Sensetivity;

	FText Nickname;
};
