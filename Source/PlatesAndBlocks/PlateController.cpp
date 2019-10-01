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
	PlatePosition PlatePos = ControlledPlate->GetPlacement();
	
	if(GameMode->IsPlaceFreeAndCorrect(PlatePos.x, PlatePos.y+1))
	{
		GameMode->SetBoard(PlatePos.x, PlatePos.y, nullptr);
		GameMode->SetBoard(PlatePos.x, PlatePos.y+1, ControlledPlate);
		ControlledPlate->SetPlacement(PlatePos.x, PlatePos.y + 1);
		ControlledPlate->MoveUp();
		auto PlateLocation = ControlledPlate->GetActorLocation();
		ControlledPlate->SetActorLocation(PlateLocation + ShiftUp*ShiftMultiply);
		IsGameCompleted = GameMode->IsGameCompleted();
	}
}

void APlateController::MovePlateDown()
{
	if (!ensure(ControlledPlate)) { return; }
	PlatePosition PlatePos = ControlledPlate->GetPlacement();

	if (GameMode->IsPlaceFreeAndCorrect(PlatePos.x, PlatePos.y - 1))
	{
		GameMode->SetBoard(PlatePos.x, PlatePos.y, nullptr);
		GameMode->SetBoard(PlatePos.x, PlatePos.y - 1, ControlledPlate);
		ControlledPlate->SetPlacement(PlatePos.x, PlatePos.y - 1);
		ControlledPlate->MoveDown();
		auto PlateLocation = ControlledPlate->GetActorLocation();
		ControlledPlate->SetActorLocation(PlateLocation + ShiftDown*ShiftMultiply);
		IsGameCompleted = GameMode->IsGameCompleted();
	}
}

void APlateController::MovePlateLeft()
{
	if (!ensure(ControlledPlate)) { return; }
	PlatePosition PlatePos = ControlledPlate->GetPlacement();

	if (GameMode->IsPlaceFreeAndCorrect(PlatePos.x -1, PlatePos.y))
	{
		GameMode->SetBoard(PlatePos.x, PlatePos.y, nullptr);
		GameMode->SetBoard(PlatePos.x - 1, PlatePos.y, ControlledPlate);
		ControlledPlate->SetPlacement(PlatePos.x - 1, PlatePos.y);
		ControlledPlate->MoveLeft();
		auto PlateLocation = ControlledPlate->GetActorLocation();
		ControlledPlate->SetActorLocation(PlateLocation + ShiftLeft*ShiftMultiply);
		IsGameCompleted = GameMode->IsGameCompleted();
	}
}

void APlateController::MovePlateRight()
{
	if (!ensure(ControlledPlate)) { return; }
	PlatePosition PlatePos = ControlledPlate->GetPlacement();

	if (GameMode->IsPlaceFreeAndCorrect(PlatePos.x + 1, PlatePos.y))
	{
		GameMode->SetBoard(PlatePos.x, PlatePos.y, nullptr);
		GameMode->SetBoard(PlatePos.x+1, PlatePos.y, ControlledPlate);
		ControlledPlate->SetPlacement(PlatePos.x+1, PlatePos.y);
		ControlledPlate->MoveRight();
		auto PlateLocation = ControlledPlate->GetActorLocation();
		ControlledPlate->SetActorLocation(PlateLocation + ShiftRight*ShiftMultiply);
		IsGameCompleted = GameMode->IsGameCompleted();
	}
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