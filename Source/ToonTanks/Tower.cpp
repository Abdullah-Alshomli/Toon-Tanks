// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/EngineTypes.h"
#include "TimerManager.h"

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Tank)
	{
		if (InRange())
		{
			RotateTurret(Tank->GetActorLocation());
		}
	}
}

void ATower::HandelDestruction()
{
	Super::HandelDestruction();
	Destroy();
}

void ATower::BeginPlay()
{
	Super::BeginPlay();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(FireRateTimeHandler, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::CheckFireCondition()
{
	if (InRange() && Tank->bTankAlive)
	{
		Fire();
	}
}

bool ATower::InRange()
{
	if (Tank)
	{
		float TankDistance = FVector::Distance(GetActorLocation(), Tank->GetActorLocation());
		if (TankDistance <= FireRange)
		{
			return true;
		}
	}
	return false;
}
