// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BaseTank.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateSpawn, APawn*,p_Pawn);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FDelegateThreeParam, float, Time, float, Rate, float, Step);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDelegateZeroParam);

USTRUCT(BlueprintType)
struct FReferenceOnElement
{

	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class Abullet> objectBullet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UNiagaraSystem* ExplosionShoot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UNiagaraSystem* ExplosionDeath;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USoundBase* Shoot_sound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UW_SuperPower> superSkillWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMaterialInstance* M_OutTeam;
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class APArticleAndSound> Shoot_effect;*/
};


UCLASS()
class MYGAME2_API ABaseTank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABaseTank();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UStaticMeshComponent* Towermesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USpringArmComponent* spring_arm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UCameraComponent* camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USceneComponent* bscene;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UAudioComponent* AudioShoot;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		class UHealthStat* HP_Component;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UCameraComponent* SecondCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UNiagaraComponent* N_ExplosionShoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FReferenceOnElement struction;

	class UGame_Interface* Main_Widget;

	

	FDelegateSpawn D_SpawnTankPawn;
	FDelegateZeroParam D_ReloadEnd;
	FDelegateThreeParam D_ReloadStart;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void Tick(float DeltaTime) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	float Speed;

	float Rotation_speed;

	float Towerrotation_speed;

	bool IsAim;

	bool isSuper_Power;

	float Damage;

	float Max_HP;
	UPROPERTY(Replicated)
	bool isReload;

	bool isReloadSuperPower;

	float TimeReload;

	float TimeReload_SuperPower;

	float TimeUse_SuperPower;

	float TimeDestroy;

	class ABaseHUD* HUD;

	class ABase_GameMode* gameMode;
private:

	float target;

	virtual void PossessedBy(AController* Controller) override;
	
	

protected:
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(NetMulticast, Reliable)
		virtual void ForwardMove(float Axis);
	UFUNCTION(Server, Reliable)
		virtual void CallForwardMove(float axis);

	UFUNCTION(NetMulticast, Reliable)
		virtual void RightMove(float Axis);
	UFUNCTION(Server, Reliable)
		virtual void CallRightMove(float axis);
	UFUNCTION()
	virtual void ClientRotateTower();
	UFUNCTION(Server, Reliable)
	void RotateTower_OnServer(float Target);

	UFUNCTION()
		void EnableAim();
	UFUNCTION()
		virtual void DisableAim();

	UFUNCTION(NetMulticast, Unreliable)
		virtual void Shoot_Multicast();
	UFUNCTION(Server, Unreliable)
		virtual void Shoot_OnServer();

	void RecharchShoot();

	UFUNCTION(Client, Unreliable)
		void Widget_ReloadShoot();

	UFUNCTION(BlueprintCallable)
	static float InterpTo(float Current, float Target, float DeltaTime, float Speed);
	//UFUNCTION(Client, Unreliable)
	//	TSubclassOf<class UW_SuperPower> GetSuperSkillWidget();
public:
	
	void Destroy();

	ABase_GameMode* GetGameMode();

	UFUNCTION(BlueprintCallable)
		float GetDamage();

	UFUNCTION(NetMulticast, Reliable)
		virtual void VisualDeadMulticast();
	UFUNCTION()
	void ActivateOurTeamMaterial();

	float GetSpeed();

	float GetRotationSpeed();

	float GetTowerRotationSpeed();

	float GetHP();

	float GetTimeReload();

	float GetTimeReloadSuperPower();

	float GetTimeUseSuperPower();

	float GetTimeDestroy();
	
};
