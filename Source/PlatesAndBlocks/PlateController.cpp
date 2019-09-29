// Fill out your copyright notice in the Description page of Project Settings.


#include "PlateController.h"
#include "Plate.h"

void APlateController::MovePlateUp()
{
	if (!ensure(ControlledPlate)) { return; }
	ControlledPlate->MoveUp();
	auto PlateLocation = ControlledPlate->GetActorLocation();
	ControlledPlate->SetActorLocation(PlateLocation + ShiftUp*ShiftMultiply);
}

void APlateController::MovePlateDown()
{
	if (!ensure(ControlledPlate)) { return; }
	ControlledPlate->MoveDown();
	auto PlateLocation = ControlledPlate->GetActorLocation();
	ControlledPlate->SetActorLocation(PlateLocation + ShiftDown*ShiftMultiply);
}

void APlateController::MovePlateLeft()
{
	if (!ensure(ControlledPlate)) { return; }
	ControlledPlate->MoveLeft();
	auto PlateLocation = ControlledPlate->GetActorLocation();
	ControlledPlate->SetActorLocation(PlateLocation + ShiftLeft*ShiftMultiply);
}

void APlateController::MovePlateRight()
{
	if (!ensure(ControlledPlate)) { return; }
	ControlledPlate->MoveRight();
	auto PlateLocation = ControlledPlate->GetActorLocation();
	ControlledPlate->SetActorLocation(PlateLocation + ShiftRight*ShiftMultiply);
}

void APlateController::SetControlledPlate(APlate* platePawn)
{
	ControlledPlate = platePawn;
}

APlate* APlateController::GetControlledPlate()
{
	return ControlledPlate;
}