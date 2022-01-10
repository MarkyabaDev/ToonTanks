// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"

#include "Components/CapsuleComponent.h"
#include "Projectile.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

void ABasePawn::HandleDestruction()
{
	// TODO: Visual / sound effects
}


void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	if (!TurretMesh)
	{
		UE_LOG(LogTemp, Error, TEXT("Turret Mesh is not set on Actor %s"), *GetName());
		return;
	}

	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator ToRotation(0, ToTarget.Rotation().Yaw, 0);

	TurretMesh->SetWorldRotation(ToRotation);
}

void ABasePawn::Fire()
{
	if (ProjectileSpawnPoint && ProjectileClass)
	{
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation());
		Projectile->SetOwner(this);
	}
}
