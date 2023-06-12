
#include "W_MainMenuOption.h"
#include <Components/Button.h>
#include <Components/ComboBoxString.h>
#include <Components/Slider.h>
#include <Components/TextBlock.h>
#include <Components/EditableTextBox.h>
#include <GameFramework/GameUserSettings.h>
#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/KismetStringLibrary.h>
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetTextLibrary.h>
#include <Kismet/GameplayStatics.h>
#include "../../Game/Save/BaseSaveGame.h"
#include "../../Game/BaseGameInstance.h"
#include "../../PawnController.h"





bool UW_MainMenuOption::Initialize()
{
	Super::Initialize();

	SensetivityX = 1.f;
	SensetivityY = 1.f;


	return true;
}



void UW_MainMenuOption::NativeConstruct()
{
	Super::NativeConstruct();

	UserSettings = UGameUserSettings::GetGameUserSettings();
	

	B_Windowed->OnClicked.AddDynamic(this, &UW_MainMenuOption::OnClickWindowedButton);
	B_BorderlessWindow->OnClicked.AddDynamic(this, &UW_MainMenuOption::OnClickBorderlessWindowButton);
	B_FullScreen->OnClicked.AddDynamic(this, &UW_MainMenuOption::OnClickFullScreenButton);
	B_Auto->OnClicked.AddDynamic(this, &UW_MainMenuOption::OnClickAutoButton);
	B_Apply->OnClicked.AddDynamic(this, &UW_MainMenuOption::OnClickApplyButton);
	B_Reset->OnClicked.AddDynamic(this, &UW_MainMenuOption::OnResetChanges);


	CB_Resolution->OnSelectionChanged.AddDynamic(this, &UW_MainMenuOption::OnSelectResolution);
	CB_AntiAliasing->OnSelectionChanged.AddDynamic(this, &UW_MainMenuOption::OnSelectAntiAliasing);
	CB_PostProcessing->OnSelectionChanged.AddDynamic(this, &UW_MainMenuOption::OnSelectPostProcessing);
	CB_Reflection->OnSelectionChanged.AddDynamic(this, &UW_MainMenuOption::OnSelectReflection);
	CB_Shading->OnSelectionChanged.AddDynamic(this, &UW_MainMenuOption::OnSelectShading);
	CB_Shadow->OnSelectionChanged.AddDynamic(this, &UW_MainMenuOption::OnSelectShadow);
	CB_Texture->OnSelectionChanged.AddDynamic(this, &UW_MainMenuOption::OnSelectTexture);
	CB_ViewDistance->OnSelectionChanged.AddDynamic(this, &UW_MainMenuOption::OnSelectViewDistance);
	CB_VisualEffect->OnSelectionChanged.AddDynamic(this, &UW_MainMenuOption::OnSelectVisualEffect);

	S_ResolutionScale->OnValueChanged.AddDynamic(this, &UW_MainMenuOption::OnChangeValue);
	S_SensetiveX->OnValueChanged.AddDynamic(this, &UW_MainMenuOption::OnSensetivityXChanges);
	S_SensetiveY->OnValueChanged.AddDynamic(this, &UW_MainMenuOption::OnSensetivityYChanges);

	UpdateInfo();

	ET_Nickname->OnTextCommitted.AddDynamic(this, &UW_MainMenuOption::OnCommitedText);

	T_PercentResolutionScale->TextDelegate.BindDynamic(this, &UW_MainMenuOption::OnBindPercentResolutionScale);
	T_PercentSensetivityX->TextDelegate.BindDynamic(this, &UW_MainMenuOption::OnBindPercentSensetivityX);
	T_PercentSensetivityY->TextDelegate.BindDynamic(this, &UW_MainMenuOption::OnBindPercentSensetivityY);
	T_PercentResolutionScale->SynchronizeProperties();
	T_PercentSensetivityX->SynchronizeProperties();
	T_PercentSensetivityY->SynchronizeProperties();

	SaveObject = Cast<UBaseSaveGame>(UGameplayStatics::CreateSaveGameObject(UBaseSaveGame::StaticClass()));

	if (IsValid(Cast<APawnController>(GetOwningPlayer())))
	{
		ET_Nickname->SetIsEnabled(false); //Disable input, if the player is not playing now
	}

}

void UW_MainMenuOption::UpdateInfo()
{
	UpdateButtonsDisplayMode();
	UpdateCurrentResolutionInfo();

	UpdateResolutionScaleQuality();
	UpdateSensetivity();
	UpdateShadowQuality();
	UpdateVisualEffectQuality();
	UpdateViewDistanceQuality();
	UpdateTextureQuality();
	UpdateShadingQuality();
	UpdateRefflectionQuality();
	UpdateAntiAliasingQuality();
	UpdatePostProcessingQuality();
	UpdateNickname();

}

void UW_MainMenuOption::UpdateButtonsDisplayMode()
{
	switch (UserSettings->GetFullscreenMode())
	{
	case EWindowMode::Type::Fullscreen:
		B_FullScreen->SetIsEnabled(false);
		B_Windowed->SetIsEnabled(true);
		B_BorderlessWindow->SetIsEnabled(true);
		break;
	case EWindowMode::Type::WindowedFullscreen:
		B_BorderlessWindow->SetIsEnabled(false);
		B_FullScreen->SetIsEnabled(true);
		B_Windowed->SetIsEnabled(true);
		break;
	case EWindowMode::Type::Windowed:
		B_Windowed->SetIsEnabled(false);
		B_FullScreen->SetIsEnabled(true);
		B_BorderlessWindow->SetIsEnabled(true);
		break;
	default:
		break;
	}
}

void UW_MainMenuOption::UpdateCurrentResolutionInfo()
{
	TArray<FIntPoint> arrResolution;
	UKismetSystemLibrary::GetSupportedFullscreenResolutions(arrResolution);

	CB_Resolution->ClearOptions();

	for (FIntPoint& el : arrResolution)
	{
		CB_Resolution->AddOption(FString::FromInt(el.X) + "x" + FString::FromInt(el.Y));
	}

	FIntPoint currentRes = UserSettings->GetScreenResolution();
	CB_Resolution->SetSelectedOption(FString::FromInt(currentRes.X) + "x" + FString::FromInt(currentRes.Y));
	

	switch (UserSettings->GetFullscreenMode())
	{
	case EWindowMode::Type::Fullscreen:
		CB_Resolution->SetIsEnabled(true);
		break;
	case EWindowMode::Type::WindowedFullscreen:
		CB_Resolution->SetIsEnabled(false);
		break;
	case EWindowMode::Type::Windowed:
		CB_Resolution->SetIsEnabled(true);
		break;
	default:
		break;
	}
}

void UW_MainMenuOption::UpdateResolutionScaleQuality()
{
	float currentNormalizedValue, currentValue,minScaleValue,maxScaleValue;
	UserSettings->GetResolutionScaleInformationEx(currentNormalizedValue, currentValue, minScaleValue, maxScaleValue);
	S_ResolutionScale->SetValue(currentNormalizedValue);
}

void UW_MainMenuOption::UpdateShadowQuality()
{
	CB_Shadow->SetSelectedIndex(UserSettings->GetShadowQuality());
}

void UW_MainMenuOption::UpdateVisualEffectQuality()
{
	CB_VisualEffect->SetSelectedIndex(UserSettings->GetVisualEffectQuality());
}

void UW_MainMenuOption::UpdateViewDistanceQuality()
{
	CB_ViewDistance->SetSelectedIndex(UserSettings->GetVisualEffectQuality());
}

void UW_MainMenuOption::UpdateTextureQuality()
{
	CB_Texture->SetSelectedIndex(UserSettings->GetTextureQuality());
}

void UW_MainMenuOption::UpdateShadingQuality()
{
	CB_Shading->SetSelectedIndex(UserSettings->GetShadingQuality());
}

void UW_MainMenuOption::UpdateRefflectionQuality()
{
	CB_Reflection->SetSelectedIndex(UserSettings->GetReflectionQuality());
}

void UW_MainMenuOption::UpdateAntiAliasingQuality()
{
	CB_AntiAliasing->SetSelectedIndex(UserSettings->GetAntiAliasingQuality());
}

void UW_MainMenuOption::UpdatePostProcessingQuality()
{
	CB_PostProcessing->SetSelectedIndex(UserSettings->GetPostProcessingQuality());
}

void UW_MainMenuOption::UpdateSensetivity()
{
	UBaseSaveGame* SaveClass = Cast<UBaseSaveGame>(UGameplayStatics::LoadGameFromSlot(CastChecked<UBaseGameInstance>(UGameplayStatics::GetGameInstance(this))->SaveSlotOptions, 0));

	if (SaveClass != nullptr)
	{
		SensetivityX = SaveClass->SensetiveX;
		SensetivityY = SaveClass->SensetiveY;
	}
	S_SensetiveX->SetValue(SensetivityX);
	S_SensetiveY->SetValue(SensetivityY);
}

void UW_MainMenuOption::UpdateNickname()
{
	UBaseSaveGame* SaveClass = Cast<UBaseSaveGame>(UGameplayStatics::LoadGameFromSlot(CastChecked<UBaseGameInstance>(UGameplayStatics::GetGameInstance(this))->SaveSlotOptions, 0));
	
	if (SaveClass != nullptr)
	{
		Nickname = SaveClass->Nickname;
	}
	ET_Nickname->SetText(Nickname);
}

FText UW_MainMenuOption::OnBindPercentResolutionScale()
{	
	return FText::FromString(UKismetTextLibrary::Conv_TextToString(UKismetTextLibrary::Conv_FloatToText(S_ResolutionScale->GetValue() * 100.f, ERoundingMode::HalfToEven, false, true, 1, 324, 1, 1)) + "%");
}

FText UW_MainMenuOption::OnBindPercentSensetivityX()
{
	return FText::FromString(UKismetTextLibrary::Conv_TextToString(UKismetTextLibrary::Conv_FloatToText(SensetivityX, ERoundingMode::HalfToEven, false, true, 1, 324, 1, 1)) + "%");
}

FText UW_MainMenuOption::OnBindPercentSensetivityY()
{
	return FText::FromString(UKismetTextLibrary::Conv_TextToString(UKismetTextLibrary::Conv_FloatToText(SensetivityY, ERoundingMode::HalfToEven, false, true, 1, 324, 1, 1)) + "%");
}

void UW_MainMenuOption::OnClickWindowedButton()
{
	UserSettings->SetFullscreenMode(EWindowMode::Windowed);
	UpdateButtonsDisplayMode();
	UpdateCurrentResolutionInfo();
}

void UW_MainMenuOption::OnClickBorderlessWindowButton()
{
	UserSettings->SetFullscreenMode(EWindowMode::WindowedFullscreen);
	UpdateButtonsDisplayMode();
	UpdateCurrentResolutionInfo();
}

void UW_MainMenuOption::OnClickFullScreenButton()
{
	UserSettings->SetFullscreenMode(EWindowMode::Fullscreen);
	UpdateButtonsDisplayMode();
	UpdateCurrentResolutionInfo();
}

void UW_MainMenuOption::OnClickAutoButton()
{
	UserSettings->RunHardwareBenchmark(10);
	UpdateInfo();
}

void UW_MainMenuOption::OnClickApplyButton()
{
	UserSettings->ApplySettings(true);
	
	if (SaveObject != nullptr)
	{
		if (SaveObject->SensetiveX != SensetivityX || SaveObject->SensetiveY != SensetivityY)
		{
			SaveObject->SensetiveX = SensetivityX;
			SaveObject->SensetiveY = SensetivityY;
			SaveObject->Nickname = Nickname;

			UGameplayStatics::AsyncSaveGameToSlot(SaveObject, Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(this))->SaveSlotOptions, 0);
		}
	}
}


void UW_MainMenuOption::OnResetChanges()
{
	UserSettings->LoadSettings();
	UpdateInfo();
}


void UW_MainMenuOption::OnSelectResolution(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	if (SelectionType == ESelectInfo::OnMouseClick)
	{
		FString sLeft, sRight;
		SelectedItem.Split(FString("x"), &sLeft, &sRight);
		UserSettings->SetScreenResolution(FIntPoint(UKismetStringLibrary::Conv_StringToInt(sLeft), UKismetStringLibrary::Conv_StringToInt(sRight)));
	}
}

void UW_MainMenuOption::OnSelectAntiAliasing(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	if (SelectionType == ESelectInfo::OnMouseClick)
	{
		UserSettings->SetAntiAliasingQuality(CB_AntiAliasing->FindOptionIndex(SelectedItem));
	}
}

void UW_MainMenuOption::OnSelectViewDistance(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	if (SelectionType == ESelectInfo::OnMouseClick)
	{
		UserSettings->SetViewDistanceQuality(CB_ViewDistance->FindOptionIndex(SelectedItem));
	}
}

void UW_MainMenuOption::OnSelectVisualEffect(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	if (SelectionType == ESelectInfo::OnMouseClick)
	{
		UserSettings->SetVisualEffectQuality(CB_VisualEffect->FindOptionIndex(SelectedItem));
	}
}

void UW_MainMenuOption::OnSelectShadow(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	if (SelectionType == ESelectInfo::OnMouseClick)
	{
		UserSettings->SetShadowQuality(CB_Shadow->FindOptionIndex(SelectedItem));
	}
}

void UW_MainMenuOption::OnSelectTexture(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	if (SelectionType == ESelectInfo::OnMouseClick)
	{
		UserSettings->SetTextureQuality(CB_Texture->FindOptionIndex(SelectedItem));
	}
}

void UW_MainMenuOption::OnSelectShading(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	if (SelectionType == ESelectInfo::OnMouseClick)
	{
		UserSettings->SetShadingQuality(CB_Shading->FindOptionIndex(SelectedItem));
	}
}

void UW_MainMenuOption::OnSelectReflection(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	if (SelectionType == ESelectInfo::OnMouseClick)
	{
		UserSettings->SetReflectionQuality(CB_Reflection->FindOptionIndex(SelectedItem));
	}
}

void UW_MainMenuOption::OnSelectPostProcessing(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	if (SelectionType == ESelectInfo::OnMouseClick)
	{
		UserSettings->SetPostProcessingQuality(CB_PostProcessing->FindOptionIndex(SelectedItem));
	}
}

void UW_MainMenuOption::OnChangeValue(float Value)
{
	UserSettings->SetResolutionScaleNormalized(Value);
}

void UW_MainMenuOption::OnSensetivityXChanges(float Value)
{
	SensetivityX = Value;
}

void UW_MainMenuOption::OnSensetivityYChanges(float Value)
{
	SensetivityY = Value;
}

void UW_MainMenuOption::OnCommitedText(const FText& Text, ETextCommit::Type CommitMethod)
{
	Nickname = Text;
}
