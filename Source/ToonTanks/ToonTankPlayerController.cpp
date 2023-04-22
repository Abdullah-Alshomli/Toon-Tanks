// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/Controller.h"
#include "ToonTankPlayerController.h"

void AToonTankPlayerController::SetPlayerEnabledState(bool bPlayerEnabled)
{
	if (bPlayerEnabled)
	{
		GetPawn()->EnableInput(this);
	}
	else
	{
		GetPawn()->DisableInput(this);
	}
	// to show the mouse and to disable it when player dies
	bShowMouseCursor = bPlayerEnabled;
}
