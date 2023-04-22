// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"

#include "Tank.h"
#include "ToonTankPlayerController.h"
#include "Tower.h"
#include "Kismet/GameplayStatics.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank)
	{
		Tank->HandelDestruction();
		if (ToonTankPlayerController)
		{
			ToonTankPlayerController->SetPlayerEnabledState(false);
		}
		GameOver(false);
	}
	else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
	{
		DestroyedTower->HandelDestruction();
		TargetTowers--;
		if (TargetTowers == 0)
		{
			GameOver(true);
		}
	}
}

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();
	HandleStart();
}

void AToonTanksGameMode::HandleStart()
{
	TargetTowers = GetTargetTowerCount();
	StartGame();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonTankPlayerController = Cast<AToonTankPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	ToonTankPlayerController->SetPlayerEnabledState(false);
	// timer
	FTimerHandle StartTimerHandel;
	FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(ToonTankPlayerController,
	                                                             &AToonTankPlayerController::SetPlayerEnabledState,
	                                                             true);
	GetWorldTimerManager().SetTimer(StartTimerHandel, TimerDelegate, StartTime, false);
}

int32 AToonTanksGameMode::GetTargetTowerCount()
{
	TArray<AActor*> Towers;
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);
	return Towers.Num();
}
