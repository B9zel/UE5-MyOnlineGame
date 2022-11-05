// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BaseTank.generated.h"




USTRUCT(BlueprintType)
struct FObject_struction
{

	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class Abullet> objctBullet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UParticleSystem* Explosion;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USoundBase* Shoot_sound;


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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UHeads_Stats* component;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UCameraComponent* SecondCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FObject_struction struction;


	class UGame_Interface* Main_Widget;

	class ABase_GameMode* GameMode;

	float TimeReload;

	float TimeReoload_SuperPower;

	float TimeUse_SuperPower;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual	void Take_Damage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	float Speed;

	float Rotation_speed;

	float Towerrotation_speed;

	bool blockShoot;

	bool IsAim;

	bool isSuper_Power;

	float Time_SpawnSpectator;

	float TimeReload_SuperPower;

	float Damage;

	float Max_HP;

private:

	float math;

	float target;

public:	
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(NetMulticast, Unreliable)
		virtual void ForwardMove(float Axis);
	UFUNCTION(Server, Unreliable)
		virtual void CallForwardMove(float axis);

	UFUNCTION(NetMulticast, Unreliable)
		virtual void RightMove(float Axis);
	UFUNCTION(Server, Unreliable)
		virtual void CallRightMove(float axis);

	virtual void ClientRotateTower(float DeltaTime);

	UFUNCTION(NetMulticast, Unreliable)
		virtual void RotateTower(float deltaTime, float Target);
	UFUNCTION(Server, Unreliable)
		virtual void CallRotateTower(float deltatime, float Target);

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

	UFUNCTION(NetMulticast, Unreliable)
		virtual void VisualDeadMulticast();

	ABase_GameMode* Get_GameMode(class AActor* Object);

	UFUNCTION(BlueprintCallable)
	float Get_Damage();

	UFUNCTION(BlueprintCallable)
	float InterpTo(float Current, float Target, float DeltaTime, float Speed);
};
