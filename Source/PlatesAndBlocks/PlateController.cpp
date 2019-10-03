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

void APlateController::SetControlledPlate(APlate* platePawn)
{
	ControlledPlate = platePawn;
}

APlate* APlateController::GetControlledPlate()
{
	return ControlledPlate;
}

void APlateController::MovePlateUp()
{	
	if (!ensure(ControlledPlate)) { return; }
	ControlledPlate->Move(ShiftUp);
}

void APlateController::MovePlateDown()
{
	if (!ensure(ControlledPlate)) { return; }
	ControlledPlate->Move(ShiftDown);
}

void APlateController::MovePlateLeft()
{
	if (!ensure(ControlledPlate)) { return; }
	ControlledPlate->Move(ShiftLeft);
}

void APlateController::MovePlateRight()
{
	if (!ensure(ControlledPlate)) { return; }
	ControlledPlate->Move(ShiftRight);
}




