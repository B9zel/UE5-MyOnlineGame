// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BaseTank.generated.h"



class UBaseTankConfigDataAsset;
class ABase_GameMode;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateSpawn, APawn*, p_Pawn);
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

};

UENUM()
enum class EDirectionMove : uint8
{
	FORWARD_MOVE = 0,
	BACK_MOVE,
	RIGHT_TURN,
	LEFT_TURN,
	FORWARD_RIGHT_MOVE,
	FORWARD_LEFT_MOVE,
	BACK_RIGHT_MOVE,
	BACK_LEFT_MOVE,
	STOP
};


UCLASS()
class MYGAME2_API ABaseTank : public APawn
{
	GENERATED_BODY()

public:

	ABaseTank();

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

	float GetTimeReload();

	float GetTimeReloadSuperPower();

	float GetTimeUseSuperPower();

	float GetTimeDestroy();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void Tick(float DeltaTime) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PossessedBy(AController* Controller) override;

	virtual void InitializeProperties() PURE_VIRTUAL(ABaseTank::InitializeProperties, );
	virtual void Shoot();

	void RecharchShoot();

	UFUNCTION(Server, Reliable)
	virtual void ChangeMoveDirection_Server(EDirectionMove NewDirection);

	UFUNCTION()
	virtual void ForwardMove();
	UFUNCTION()
	virtual void BackMove();

	void ForwardMove_OnClient(float Axis);
	void BackMove_OnClient(float Axis);

	void ForwardInputMove(float Axis);

	virtual void RightTurn();
	virtual void LeftTurn();

	virtual void RightTurn_Server(float Axis);
	virtual void LeftTurn_Server(float Axis);


	void RotateInputMove(float Axis);


	UFUNCTION()
	virtual void ClientRotateTower();
	void Move_OnClient();
	UFUNCTION(Server, Reliable)
	void RotateTower_OnServer(float Target);

	UFUNCTION()
	void EnableAim();
	UFUNCTION()
	virtual void DisableAim();

	UFUNCTION(Client, Unreliable)
	void Widget_ReloadShoot();

	UFUNCTION(BlueprintCallable)
	static float InterpTo(float Current, float Target, float DeltaTime, float Speed);

	UFUNCTION(NetMulticast, Reliable)
	virtual void Shoot_Multicast();
	UFUNCTION(Server, Reliable)
	virtual void Shoot_OnServer(float YawRotateTower);

private:

	void SetTowerRotationServer(const float YawValue);

	UFUNCTION(Client, Unreliable)
	void SetTowerRotation_OnClient(const float ValueYaw);

public:

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
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

	float Speed;

	float Rotation_speed;

	float Towerrotation_speed;

	float Damage;

	float TimeReload;

	float TimeReload_SuperPower;

	float TimeUse_SuperPower;

	float TimeDestroy;


	UPROPERTY(Replicated)
	bool isReload;

	UPROPERTY(Replicated)
	float TargetYawRotation;

	bool IsAim;
	bool isSuper_Power;
	bool isReloadSuperPower;

	EDirectionMove Direction;

	class ABaseHUD* HUD;

	class ABase_GameMode* gameMode;

private:

	UPROPERTY(EditAnywhere, meta = (ClampMin = "-180.0", ClampMax = "0.0"))
	float MinDigressRotateTower;
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0", ClampMax = "180.0"))
	float MaxDigressRotateTower;
	UPROPERTY(VisibleDefaultsOnly, meta = (ClampMin = "0.0"), Category = "Net")
	float MaxDegressOutOfSyncRotation;
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0"), Category = "Net")
	float MaxDistanceOutOfSyncLocation;
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0"), Category = "Net")
	float MaxDistanceOutOfSyncRotation;

	UPROPERTY(Replicated)
	FVector TargetLocation;
	UPROPERTY(Replicated)
	FRotator TargetRotation;
};
