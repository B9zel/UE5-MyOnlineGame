// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BaseTank.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateSpawn, TSubclassOf<UW_SuperPower>,Widget);

USTRUCT(BlueprintType)
struct FReferenceOnElement
{

	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class Abullet> objctBullet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UParticleSystem* Explosion;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USoundBase* Shoot_sound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UW_SuperPower> superSkillWidgetClass;
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
		class UProjectileMovementComponent* projectile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USceneComponent* bscene;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		class UHealthStat* HP_Component;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UCameraComponent* SecondCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FReferenceOnElement struction;

	class UGame_Interface* Main_Widget;

	class ABase_GameMode* GameMode;

	float TimeReload;

	float TimeReload_SuperPower;

	float TimeUse_SuperPower;

	float TimeDestroy;

	FDelegateSpawn D_SpawnTankPawn;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	float Speed;

	float Rotation_speed;

	float Towerrotation_speed;

	bool blockShoot;

	bool IsAim;

	bool isSuper_Power;

	float Damage;

	float Max_HP;

private:

	float math;

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
		void DisableAim();

	UFUNCTION(NetMulticast, Unreliable)
		virtual void Shoot_Multicast();
	UFUNCTION(Server, Unreliable)
		virtual void Shoot_OnServer();

	void RecharchShoot();

	UFUNCTION(Client, Unreliable)
		void Widget_ReloadShoot();

	UFUNCTION(BlueprintCallable)
		float InterpTo(float Current, float Target, float DeltaTime, float Speed);
	//UFUNCTION(Client, Unreliable)
	//	TSubclassOf<class UW_SuperPower> GetSuperSkillWidget();
public:
	
	void Destroy();

	ABase_GameMode* Get_GameMode(class AActor* Object);

	UFUNCTION(BlueprintCallable)
		float GetDamage();

	UFUNCTION(NetMulticast, Reliable)
		virtual void VisualDeadMulticast();
	
};
