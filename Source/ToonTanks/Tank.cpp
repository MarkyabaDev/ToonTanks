// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank()
{
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComp->SetupAttachment(SpringArmComp);
}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	PlayerControllerRef = Cast<APlayerController, AController>(GetController());
}

void ATank::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (PlayerControllerRef)
	{
		FHitResult HitResult;
		PlayerControllerRef->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);

		RotateTurret(HitResult.ImpactPoint);
	}
}


void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}

void ATank::MoveForward(const float Value)
{
	const float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	const FVector DeltaLocation(Value * DeltaTime * Speed, 0, 0);
	AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(const float Value)
{
	const float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	const FRotator DeltaRotation(0, Value * DeltaTime * TurnRate, 0);

	AddActorLocalRotation(DeltaRotation, true);
}
