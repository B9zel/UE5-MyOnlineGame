
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Game_Spectator.generated.h"

UCLASS()
class MYGAME2_API AGame_Spectator : public APawn
{
	GENERATED_BODY()
public:

	AGame_Spectator();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USpringArmComponent* Spring_Arm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCameraComponent* Camera;

	UPROPERTY(Replicated,EditAnywhere, BlueprintReadWrite)
	class ABaseTank* FollowPawn;
	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

};
