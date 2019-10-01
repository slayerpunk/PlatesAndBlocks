// Fill out your copyright notice in the Description page of Project Settings.


#include "PlateController.h"
#include "Plate.h"
#include "Desk.h"
#include "PlatesAndBlocksGameModeBase.h"
#include "Kismet\GameplayStatics.h"
#include "GameFramework\Actor.h"

void APlateController::BeginPlay()
{
	Super::BeginPlay();
	GameMode = Cast<APlatesAndBlocksGameModeBase>(GetWorld()->GetAuthGameMode());

	
}
void APlateController::MovePlateUp()
{	
	if (!ensure(ControlledPlate)) { return; }
	ControlledPlate->Move(ShiftUp, 0, 1);
}

void APlateController::MovePlateDown()
{
	if (!ensure(ControlledPlate)) { return; }
	ControlledPlate->Move(ShiftDown, 0, -1);
}

void APlateController::MovePlateLeft()
{
	if (!ensure(ControlledPlate)) { return; }
	ControlledPlate->Move(ShiftLeft, -1, 0);
}

void APlateController::MovePlateRight()
{
	if (!ensure(ControlledPlate)) { return; }
	ControlledPlate->Move(ShiftRight, 1, 0);
}

bool APlateController::GetGameState()
{
	if(IsGameCompleted)
	{
		ControlledPlate = nullptr;
	}
	return IsGameCompleted;
}

void APlateController::SetControlledPlate(APlate* platePawn)
{
	ControlledPlate = platePawn;
}

void APlateController::SetDesk(ADesk * Desk_BP)
{
	Desk = Desk_BP;
}

APlate* APlateController::GetControlledPlate()
{
	return ControlledPlate;
}