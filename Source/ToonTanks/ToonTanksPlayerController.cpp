// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksPlayerController.h"

void AToonTanksPlayerController::SetPlayerEnabledState(bool bPlayerState)
{
	if (bPlayerState)
	{
		GetPawn()->EnableInput(this);
	} else
	{
		GetPawn()->DisableInput(this);
	}

	bShowMouseCursor = bPlayerState;
}
