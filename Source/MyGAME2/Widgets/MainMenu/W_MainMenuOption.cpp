
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
#include <Kismet/KismetInternationalizationLibrary.h>
#include <Kismet/GameplayStatics.h>
#include "W_BindKeyOptions.h"
#include "../../Game/BaseGameInstance.h"
#include "../../Game/Save/BaseSaveGame.h"
#include "../../PawnController.h"
#include "../../Enums/E_PlayerSpace.h"





bool UW_MainMenuOption::Initialize()
{
	Super::Initialize();

	Sensetivity.X = 1.f;
	Sensetivity.Y = 1.f;

	CB_SwitchLanguage->AddOption(TextLanguageEnglish.ToString());
	CB_SwitchLanguage->AddOption(TextLanguageRussian.ToString());


	

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
	CB_SwitchLanguage->OnSelectionChanged.AddDynamic(this, &UW_MainMenuOption::OnSelectSwitchLanguage);

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
	

	int i = 0;
	for (auto& el : UKismetInternationalizationLibrary::GetLocalizedCultures())
	{
		if (el == UKismetInternationalizationLibrary::GetCurrentLanguage())
			CB_SwitchLanguage->SetSelectedIndex(i);

		++i;
	}


	if (Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(this))->PlayerSpace == E_PlayerSpace::inGame)
	{
		ET_Nickname->SetIsEnabled(false); //Disable input, if the player is playing now
	}
	D_ChangeNickName.Broadcast(Nickname);
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
	UBaseSaveGame* SaveClass = Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(this))->GetLoadFromOptionsSlot();
	if (SaveClass != nullptr)
	{
		Sensetivity = FMath::Clamp(SaveClass->Sensetive, FVector2D(1.0,1.0), FVector2D(S_SensetiveX->GetMaxValue(), S_SensetiveY->GetMaxValue()));
	}
	S_SensetiveX->SetValue(Sensetivity.X);
	S_SensetiveY->SetValue(Sensetivity.Y);
}

void UW_MainMenuOption::UpdateNickname()
{
	UBaseSaveGame* SaveClass = Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(this))->GetLoadFromOptionsSlot();
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
	return FText::FromString(UKismetTextLibrary::Conv_TextToString(UKismetTextLibrary::Conv_FloatToText(Sensetivity.X, ERoundingMode::HalfToEven, false, true, 1, 324, 1, 1)) + "%");
}

FText UW_MainMenuOption::OnBindPercentSensetivityY()
{
	return FText::FromString(UKismetTextLibrary::Conv_TextToString(UKismetTextLibrary::Conv_FloatToText(Sensetivity.Y, ERoundingMode::HalfToEven, false, true, 1, 324, 1, 1)) + "%");
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
	
	UBaseSaveGame* SaveObject = Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(this))->GetSaveObject();
	UBaseSaveGame* SaveSlot = Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(this))->GetLoadFromOptionsSlot();
	if (SaveObject != nullptr)
	{
		if (SaveSlot != nullptr)
		{
			SaveToObjectSensetivity(SaveObject, SaveSlot->Sensetive, Sensetivity);
			SaveToObjectNickname(SaveObject, SaveSlot->Nickname, Nickname);
		}
		else
		{
			SaveToObjectSensetivity(SaveObject, FVector2D(0), Sensetivity);
			SaveToObjectNickname(SaveObject, FText::FromString(""), Nickname);			
		}
		Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(this))->SaveObjectToSlot(SaveObject);
	}
	UserSettings->ApplySettings(true);
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

void UW_MainMenuOption::OnSelectSwitchLanguage(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	if (ESelectInfo::Type::OnMouseClick == SelectionType)
	{
		
		int i = 0;
		for (auto & el : UKismetInternationalizationLibrary::GetLocalizedCultures())
		{
			if (i == CB_SwitchLanguage->FindOptionIndex(SelectedItem))
			{
				UKismetInternationalizationLibrary::SetCurrentCulture(el, true);
				break;
			}

			++i;
		}
		CB_SwitchLanguage->ClearOptions();
		CB_SwitchLanguage->AddOption(TextLanguageEnglish.ToString());
		CB_SwitchLanguage->AddOption(TextLanguageRussian.ToString());
		CB_SwitchLanguage->SetSelectedIndex(i);
	}
}

void UW_MainMenuOption::OnChangeValue(float Value)
{
	UserSettings->SetResolutionScaleNormalized(Value);
}

void UW_MainMenuOption::OnSensetivityXChanges(float Value)
{
	Sensetivity.X = Value;
}

void UW_MainMenuOption::OnSensetivityYChanges(float Value)
{
	Sensetivity.Y = Value;
}

void UW_MainMenuOption::OnCommitedText(const FText& Text, ETextCommit::Type CommitMethod)
{
	Nickname = Text;
}

void UW_MainMenuOption::SaveToObjectSensetivity(class UBaseSaveGame* const SaveObject, const FVector2D SavedSensetivityInSlot, const FVector2D Sens)
{
	if (SavedSensetivityInSlot != Sens)
	{
		SaveObject->Sensetive = Sens;
		D_OptionSensetivity.Broadcast(Sens);
	}
	else
	{
		SaveObject->Sensetive = SavedSensetivityInSlot;
	}
}

void UW_MainMenuOption::SaveToObjectNickname(UBaseSaveGame* const SaveObject, const FText SavedNickInSlot, const FText Nick)
{
	FText s = Nick;
	UE_LOG(LogTemp, Warning, TEXT("%s"), *s.ToString());
	if (UKismetTextLibrary::NotEqual_TextText(SavedNickInSlot, Nick))
	{
		if (!Nick.IsEmpty())
		{
			SaveObject->Nickname = Nick;
		}
	}
	else
	{
		SaveObject->Nickname = SavedNickInSlot;
	}
	D_ChangeNickName.Broadcast(Nick);
}
