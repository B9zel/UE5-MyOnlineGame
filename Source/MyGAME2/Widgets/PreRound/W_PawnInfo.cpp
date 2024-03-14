// Fill out your copyright notice in the Description page of Project Settings.


#include "W_PawnInfo.h"
#include <Components/WidgetSwitcher.h>
#include <Components/TextBlock.h>
#include "Internationalization/TextTransformer.h" 
#include <Kismet/KismetTextLibrary.h>
#include "../../Pawns/HeavyTank.h"
#include "../../Pawns/Light_Tank.h"
#include "../../Pawns/Medium_Tank.h"
#include "../../Pawns/Stealth_Tank.h"




void UW_PawnInfo::SetSwitchInfo(E_AllPawns E_pawm)
{
	switch (E_pawm)
	{
	case LightTank:
		InfoForPawn->SetText(*PawnsInfo.Find(E_AllPawns::LightTank));
		//WS_Info->SetActiveWidgetIndex(E_AllPawns::LightTank);
		break;
	case MediumTank:
		InfoForPawn->SetText(*PawnsInfo.Find(E_AllPawns::MediumTank));
		//WS_Info->SetActiveWidgetIndex(E_AllPawns::LightTank);
		break;
	case HeavyTank:
		InfoForPawn->SetText(*PawnsInfo.Find(E_AllPawns::HeavyTank));
		//WS_Info->SetActiveWidgetIndex(E_AllPawns::LightTank);
		break;
	case StelsTank:
		InfoForPawn->SetText(*PawnsInfo.Find(E_AllPawns::StelsTank));
		//WS_Info->SetActiveWidgetIndex(E_AllPawns::LightTank);
		break;
	case TotalPawns:
		break;
	default:
		break;
	}
}

void UW_PawnInfo::NativeConstruct()
{
	Super::NativeConstruct();

	
	
	PawnsInfo.Add(E_AllPawns::LightTank, GetLightTankInfo());
	PawnsInfo.Add(E_AllPawns::HeavyTank, GetHeavyTankInfo());
	PawnsInfo.Add(E_AllPawns::MediumTank, GetMediumTankInfo());
	PawnsInfo.Add(E_AllPawns::StelsTank, GetStealthTankInfo());
	
}

bool UW_PawnInfo::Initialize()
{
	Super::Initialize();

	
	//FText lightTank = *PawnsInfo.Find(E_AllPawns::LightTank);
	//FText TestHUDDisplay = NSLOCTEXT("Namespace", "key", TEXT("%s", PawnsInfo.FindRef(E_AllPawns::LightTank)),);
	return true;
}

FText UW_PawnInfo::GetLightTankInfo()
{
	FString Info;
	ALight_Tank* pawn = GetWorld()->SpawnActor<ALight_Tank>(ALight_Tank::StaticClass(), FVector(0, 0, -500),FRotator(0,0,0));

	if (pawn != nullptr)
	{
		
		Info = "\t\t\t" + UKismetTextLibrary::Conv_TextToString(TextLightTank) +
			"\n" + UKismetTextLibrary::Conv_TextToString(TextSpeedTank) + FString::FromInt(pawn->GetSpeed()) +
			"\n" + UKismetTextLibrary::Conv_TextToString(TextRotationSpeedTank) + FString::FromInt(pawn->GetRotationSpeed()) +
			"\n" + UKismetTextLibrary::Conv_TextToString(TextTowerRotationSpeedTank) + FString::FromInt(pawn->GetTowerRotationSpeed()) +
			"\n" + UKismetTextLibrary::Conv_TextToString(TextDamageTank) + FString::FromInt(pawn->GetDamage()) +
			"\n" + UKismetTextLibrary::Conv_TextToString(TextHPTank) + FString::FromInt(pawn->GetHP()) +
			"\n" + UKismetTextLibrary::Conv_TextToString(TextTimeReloadTank) + FString::FromInt(pawn->GetTimeReload()) + UKismetTextLibrary::Conv_TextToString(TextSeconds) +
			"\n\n" + UKismetTextLibrary::Conv_TextToString(TextSkillLightTank) +
			"\n" + UKismetTextLibrary::Conv_TextToString(TextSkillTimeReloadTank) + FString::FromInt(pawn->GetTimeReloadSuperPower()) + UKismetTextLibrary::Conv_TextToString(TextSeconds) +
			"\n" + UKismetTextLibrary::Conv_TextToString(TextSkillTimeUseTank) + FString::FromInt(pawn->GetTimeUseSuperPower()) + UKismetTextLibrary::Conv_TextToString(TextSeconds);
	
		pawn->Destroy();
	}
	
	return FText::FromString(Info);
}

FText UW_PawnInfo::GetMediumTankInfo()
{
	FString Info;
	AMedium_Tank* pawn = GetWorld()->SpawnActor<AMedium_Tank>(AMedium_Tank::StaticClass(), FVector(0, 0, -500), FRotator(0, 0, 0));

	if (pawn != nullptr)
	{
		Info = "\t\t\t" + UKismetTextLibrary::Conv_TextToString(TextMediumTank) +
			"\n" + UKismetTextLibrary::Conv_TextToString(TextSpeedTank) + FString::FromInt(pawn->GetSpeed()) +
			"\n" + UKismetTextLibrary::Conv_TextToString(TextRotationSpeedTank) + FString::FromInt(pawn->GetRotationSpeed()) +
			"\n" + UKismetTextLibrary::Conv_TextToString(TextTowerRotationSpeedTank) + FString::FromInt(pawn->GetTowerRotationSpeed()) +
			"\n" + UKismetTextLibrary::Conv_TextToString(TextDamageTank) + FString::FromInt(pawn->GetDamage()) +
			"\n" + UKismetTextLibrary::Conv_TextToString(TextHPTank) + FString::FromInt(pawn->GetHP()) +
			"\n" + UKismetTextLibrary::Conv_TextToString(TextTimeReloadTank) + FString::FromInt(pawn->GetTimeReload()) + UKismetTextLibrary::Conv_TextToString(TextSeconds) +
			"\n\n" + UKismetTextLibrary::Conv_TextToString(TextSkillMediumTank) +
			"\n" + UKismetTextLibrary::Conv_TextToString(TextSkillTimeReloadTank) + FString::FromInt(pawn->GetTimeReloadSuperPower()) + UKismetTextLibrary::Conv_TextToString(TextSeconds) +
			"\n" + UKismetTextLibrary::Conv_TextToString(TextSkillTimeUseTank) + FString::FromInt(pawn->GetTimeUseSuperPower()) + UKismetTextLibrary::Conv_TextToString(TextSeconds);

		pawn->Destroy();
	}
	return FText::FromString(Info);
}

FText UW_PawnInfo::GetStealthTankInfo()
{
	FString Info;
	AStealth_Tank* pawn = GetWorld()->SpawnActor<AStealth_Tank>(AStealth_Tank::StaticClass(), FVector(0, 0, -500), FRotator(0, 0, 0));

	if (pawn != nullptr)
	{
		Info = "\t\t\t" + UKismetTextLibrary::Conv_TextToString(TextStealthTank) +
			"\n" + UKismetTextLibrary::Conv_TextToString(TextSpeedTank) + FString::FromInt(pawn->GetSpeed()) +
			"\n" + UKismetTextLibrary::Conv_TextToString(TextRotationSpeedTank) + FString::FromInt(pawn->GetRotationSpeed()) +
			"\n" + UKismetTextLibrary::Conv_TextToString(TextTowerRotationSpeedTank) + FString::FromInt(pawn->GetTowerRotationSpeed()) +
			"\n" + UKismetTextLibrary::Conv_TextToString(TextDamageTank) + FString::FromInt(pawn->GetDamage()) +
			"\n" + UKismetTextLibrary::Conv_TextToString(TextHPTank) + FString::FromInt(pawn->GetHP()) +
			"\n" + UKismetTextLibrary::Conv_TextToString(TextTimeReloadTank) + FString::FromInt(pawn->GetTimeReload()) + UKismetTextLibrary::Conv_TextToString(TextSeconds) +
			"\n\n" + UKismetTextLibrary::Conv_TextToString(TextSkillStealthTank) +
			"\n" + UKismetTextLibrary::Conv_TextToString(TextSkillTimeReloadTank) + FString::FromInt(pawn->GetTimeReloadSuperPower()) + UKismetTextLibrary::Conv_TextToString(TextSeconds) +
			"\n" + UKismetTextLibrary::Conv_TextToString(TextSkillTimeUseTank) + FString::FromInt(pawn->GetTimeUseSuperPower()) + UKismetTextLibrary::Conv_TextToString(TextSeconds);

		pawn->Destroy();
	}
	return FText::FromString(Info);
}

FText UW_PawnInfo::GetHeavyTankInfo()
{
	FString Info;
	AHeavyTank* pawn = GetWorld()->SpawnActor<AHeavyTank>(AHeavyTank::StaticClass(), FVector(0, 0, -500), FRotator(0, 0, 0));

	if (pawn != nullptr)
	{
		Info = "\t\t\t" + UKismetTextLibrary::Conv_TextToString(TextHeavyTank) +
			"\n" + UKismetTextLibrary::Conv_TextToString(TextSpeedTank) + FString::FromInt(pawn->GetSpeed()) +
			"\n" + UKismetTextLibrary::Conv_TextToString(TextRotationSpeedTank) + FString::FromInt(pawn->GetRotationSpeed()) +
			"\n" + UKismetTextLibrary::Conv_TextToString(TextTowerRotationSpeedTank) + FString::FromInt(pawn->GetTowerRotationSpeed()) +
			"\n" + UKismetTextLibrary::Conv_TextToString(TextDamageTank) + FString::FromInt(pawn->GetDamage()) +
			"\n" + UKismetTextLibrary::Conv_TextToString(TextHPTank) + FString::FromInt(pawn->GetHP()) +
			"\n" + UKismetTextLibrary::Conv_TextToString(TextTimeReloadTank) + FString::FromInt(pawn->GetTimeReload()) + UKismetTextLibrary::Conv_TextToString(TextSeconds) +
			"\n\n" + UKismetTextLibrary::Conv_TextToString(TextSkillHeavyTank) +
			"\n" + UKismetTextLibrary::Conv_TextToString(TextSkillTimeReloadTank) + FString::FromInt(pawn->GetTimeReloadSuperPower()) + UKismetTextLibrary::Conv_TextToString(TextSeconds) +
			"\n" + UKismetTextLibrary::Conv_TextToString(TextSkillTimeUseTank) + FString::FromInt(pawn->GetTimeUseSuperPower()) + UKismetTextLibrary::Conv_TextToString(TextSeconds);		pawn->Destroy();
	}
	return FText::FromString(Info);
}

FText UW_PawnInfo::GetRULightTankInfo()
{
	FString Info;
	ALight_Tank* pawn = GetWorld()->SpawnActor<ALight_Tank>(ALight_Tank::StaticClass(), FVector(0, 0, -500), FRotator(0, 0, 0));

	if (pawn != nullptr)
	{
		/*Info = ("\t\t\tЛегкий танк") +  
			FString(("\nСкорость: " + FString::FromInt(pawn->GetSpeed()))) +
			FString(("\nСкорость поворота: " + FString::FromInt(pawn->GetRotationSpeed()))) +
			FString(("\nСкорость поворота башни: " + FString::FromInt(pawn->GetTowerRotationSpeed()))) +
			FString(("\nУрон: " + FString::FromInt(pawn->GetDamage()))) +
			FString(("Здоровья(HP): " + FString::FromInt(pawn->GetHP())) +
			FString(("Время перезарядки: " + FString::FromInt(pawn->GetTimeReload()) + " секунд")) +
			FString(("Способность: Ускорение")) +
			FString(("\nВремя перезарядки способности: " + FString::FromInt(pawn->GetTimeReloadSuperPower()) + " секунд")) +
			FString(("Время использования способности: " + FString::FromInt(pawn->GetTimeUseSuperPower()) + " секунд")));
	*/
		pawn->Destroy();
	}
	
	return FText::FromString(Info);
}

FText UW_PawnInfo::GetRUMediumTankInfo()
{
	FString Info;
	AMedium_Tank* pawn = GetWorld()->SpawnActor<AMedium_Tank>(AMedium_Tank::StaticClass(), FVector(0, 0, -500), FRotator(0, 0, 0));

	if (pawn != nullptr)
	{
		/*Info = "\t\t\tСредний танк"
			"\nСкорость: " + FString::FromInt(pawn->GetSpeed()) +
			"\nСкорость поворота: " + FString::FromInt(pawn->GetRotationSpeed()) +
			"\nСкорость поворота башни: " + FString::FromInt(pawn->GetTowerRotationSpeed()) +
			"\nУрон: " + FString::FromInt(pawn->GetDamage()) +
			"\nЗдоровья(HP): " + FString::FromInt(pawn->GetHP()) +" \n"
			"Время перезарядки: " + FString::FromInt(pawn->GetTimeReload()) + " секунд\n\n" +
			FString("Способность: Иммунитет к атакам") + 
			"\nВремя перезарядки способности: " + FString::FromInt(pawn->GetTimeReloadSuperPower()) + " секунд"+  
			+ "Время использования способности: " + FString::FromInt(pawn->GetTimeUseSuperPower()) + " секунд";*/

		pawn->Destroy();
	}
	
	return FText::FromString(Info);
}

FText UW_PawnInfo::GetRUStealthTankInfo()
{
	FString Info;
	AStealth_Tank* pawn = GetWorld()->SpawnActor<AStealth_Tank>(AStealth_Tank::StaticClass(), FVector(0, 0, -500), FRotator(0, 0, 0));

	if (pawn != nullptr)
	{
		/*Info = "\t\t\tСтелс танк"
			"\nСкорость: " + FString::FromInt(pawn->GetSpeed()) +
			"\nСкорость поворота: " + FString::FromInt(pawn->GetRotationSpeed()) +
			"\nСкорость поворота башни: " + FString::FromInt(pawn->GetTowerRotationSpeed()) +
			"\nУрон: " + FString::FromInt(pawn->GetDamage()) +
			"\nЗдоровья(HP): " + FString::FromInt(pawn->GetHP()) +
			"\nВремя перезарядки: " + FString::FromInt(pawn->GetTimeReload()) + " секунд" +
			"\n\nСпособность: Невидимость" +
			"\nВремя перезарядки способности: " + FString::FromInt(pawn->GetTimeReloadSuperPower()) + " секунд" +
			"\nВремя использования способности: " + FString::FromInt(pawn->GetTimeUseSuperPower()) + " секунд";*/

		pawn->Destroy();
	}

	return FText::FromString(Info);
}

FText UW_PawnInfo::GetRUHeavyTankInfo()
{
	FString Info;
	AHeavyTank* pawn = GetWorld()->SpawnActor<AHeavyTank>(AHeavyTank::StaticClass(), FVector(0, 0, -500), FRotator(0, 0, 0));

	if (pawn != nullptr)
	{
	/*	Info = "\t\t\tТяжелый танк"
			"\nСкорость: " + FString::FromInt(pawn->GetSpeed()) +
			"\nСкорость поворота: " + FString::FromInt(pawn->GetRotationSpeed()) +
			"\nСкорость поворота башни: " + FString::FromInt(pawn->GetTowerRotationSpeed()) +
			"\nУрон: " + FString::FromInt(pawn->GetDamage()) +
			"\nЗдоровья(HP): " + FString::FromInt(pawn->GetHP()) +
			"\nВремя перезарядки: " + FString::FromInt(pawn->GetTimeReload()) + " секунд" +
			"\n\nСпособность: Невидимость" +
			"\nВремя перезарядки способности: " + FString::FromInt(pawn->GetTimeReloadSuperPower()) + " секунд" +
			"\nВремя использования способности: " + FString::FromInt(pawn->GetTimeUseSuperPower()) + " секунд";*/

		pawn->Destroy();
	}

	return FText::FromString(Info);
}
