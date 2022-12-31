
#include "Game_Spectator.h"
#include <GameFramework/SpringArmComponent.h>
#include <Net/UnrealNetwork.h>
#include <Camera/CameraComponent.h>
#include <Math/UnrealMathUtility.h>
#include <Engine/EngineTypes.h>
#include "PawnController.h"
#include <MyGAME2/BaseTank.h>


AGame_Spectator::AGame_Spectator()
{
	PrimaryActorTick.bCanEverTick = true;

	SetReplicates(true);
	
	Spring_Arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	Spring_Arm->SetupAttachment(RootComponent);
	Spring_Arm->bDoCollisionTest = true;
	Spring_Arm->bInheritRoll = false;
	Spring_Arm->bUsePawnControlRotation = true;
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(Spring_Arm);
	
//	Camera->SetRelativeRotation(FRotator(10.0f, 0.0f, 0.0f));
	//UCollisionProfile::GetChannelAndResponseParams("Spectator", ECollisionChannel::ECC_GameTraceChannel1, FCollisionResponseParams::DefaultResponseParam);
	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;
		
	FollowSpeed = 4.0f;
}


void AGame_Spectator::BeginPlay()
{
	Super::BeginPlay();
	
	FTimerHandle handle;
	GetWorldTimerManager().SetTimer(handle, this, &AGame_Spectator::SpeedUpSpectator, 1.5f, false);
}

void AGame_Spectator::SpeedUpSpectator()
{
	FollowSpeed = 70.0f;
}


void AGame_Spectator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (FollowPawn != nullptr && !HasAuthority())
	{
		SetActorLocation(FMath::VInterpTo(GetActorLocation(), FollowPawn->spring_arm->GetComponentLocation(), DeltaTime, FollowSpeed));
	}
	//UE_LOG(LogTemp, Warning, TEXT("Output %f"), GetControlRotation().);
}


void AGame_Spectator::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AGame_Spectator::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(AGame_Spectator, FollowPawn, COND_OwnerOnly);
}
