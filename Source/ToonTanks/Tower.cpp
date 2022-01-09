// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"

#include "Tank.h"
#include "Kismet/GameplayStatics.h"

void ATower::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (IsTankInDistance())
	{
		RotateTurret(Tank->GetActorLocation());
	}
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::CheckFireCondition()
{
	if (IsTankInDistance())
	{
		Fire();
	}
}

bool ATower::IsTankInDistance()
{
	if (Tank)
	{
		const float DistanceToTank = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
		if (DistanceToTank <= FiringRange)
		{
			return true;
		}
	}

	return false;
}

