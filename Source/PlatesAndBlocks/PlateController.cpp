// Fill out your copyright notice in the Description page of Project Settings.


#include "PlateController.h"
#include "Plate.h"
#include "Desk.h"

void APlateController::MovePlateUp()
{
	if (!ensure(ControlledPlate)) { return; }
	PlatePosition PlatePos = ControlledPlate->GetPlacement();
	
	if(Desk->IsPlaceFreeAndCorrect(PlatePos.x, PlatePos.y+1))
	{
		Desk->SetBoard(PlatePos.x, PlatePos.y, 0);
		Desk->SetBoard(PlatePos.x, PlatePos.y+1, 1);
		ControlledPlate->SetPlacement(PlatePos.x, PlatePos.y + 1);
		ControlledPlate->MoveUp();
		auto PlateLocation = ControlledPlate->GetActorLocation();
		ControlledPlate->SetActorLocation(PlateLocation + ShiftUp*ShiftMultiply);
	}
}

void APlateController::MovePlateDown()
{
	if (!ensure(ControlledPlate)) { return; }
	PlatePosition PlatePos = ControlledPlate->GetPlacement();

	if (Desk->IsPlaceFreeAndCorrect(PlatePos.x, PlatePos.y - 1))
	{
		Desk->SetBoard(PlatePos.x, PlatePos.y, 0);
		Desk->SetBoard(PlatePos.x, PlatePos.y - 1, 1);
		ControlledPlate->SetPlacement(PlatePos.x, PlatePos.y - 1);
		ControlledPlate->MoveDown();
		auto PlateLocation = ControlledPlate->GetActorLocation();
		ControlledPlate->SetActorLocation(PlateLocation + ShiftDown*ShiftMultiply);
	}
}

void APlateController::MovePlateLeft()
{
	if (!ensure(ControlledPlate)) { return; }
	PlatePosition PlatePos = ControlledPlate->GetPlacement();

	if (Desk->IsPlaceFreeAndCorrect(PlatePos.x -1, PlatePos.y))
	{
		Desk->SetBoard(PlatePos.x, PlatePos.y, 0);
		Desk->SetBoard(PlatePos.x - 1, PlatePos.y, 1);
		ControlledPlate->SetPlacement(PlatePos.x - 1, PlatePos.y);
		ControlledPlate->MoveLeft();
		auto PlateLocation = ControlledPlate->GetActorLocation();
		ControlledPlate->SetActorLocation(PlateLocation + ShiftLeft*ShiftMultiply);
	}
}

void APlateController::MovePlateRight()
{
	if (!ensure(ControlledPlate)) { return; }
	PlatePosition PlatePos = ControlledPlate->GetPlacement();

	if (Desk->IsPlaceFreeAndCorrect(PlatePos.x + 1, PlatePos.y))
	{
		Desk->SetBoard(PlatePos.x, PlatePos.y, 0);
		Desk->SetBoard(PlatePos.x+1, PlatePos.y, 1);
		ControlledPlate->SetPlacement(PlatePos.x+1, PlatePos.y);
		ControlledPlate->MoveRight();
		auto PlateLocation = ControlledPlate->GetActorLocation();
		ControlledPlate->SetActorLocation(PlateLocation + ShiftRight*ShiftMultiply);
	}
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