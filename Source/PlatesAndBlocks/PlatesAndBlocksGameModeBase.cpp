// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatesAndBlocksGameModeBase.h"
#include "Block.h"
#include "PlateController.h"
#include "Desk.h"
APlatesAndBlocksGameModeBase::APlatesAndBlocksGameModeBase()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
		
	BoardActorsArray = new AActor**[Height]; 
	for (int count = 0; count < Height; count++)
	{
		BoardActorsArray[count] = new AActor*[Width];
	}
					
}
void APlatesAndBlocksGameModeBase::BeginPlay()
{
	//Initialize Color array
		Super::BeginPlay();
	for (int i = 0; i < QtyEachColorPlates; i++)
	{
		PlateColorsArr.Add(EPlateColor::Blue);
		PlateColorsArr.Add(EPlateColor::Yellow);
		PlateColorsArr.Add(EPlateColor::Red);
	}

	//Reset Board Actors Array Every Start or Repeat Game
	if (!ensure(BoardActorsArray)) { return; }
	for (int32 x = 0; x < Width; x++)
	{
		for (int32 y = 0; y < Height; y++)
		{
			BoardActorsArray[x][y] = nullptr;
		}
	}

	//At First Spawn Game Desk
	//After that begin spawn plates and block 
	//Plates Spawning at every even or zero column (start from 0)
	//Blocks Spawning at odd columns and only at even or 0 rows (start from 0)
	//A new plate at begin play calling GetRandomColor Method to colorize the plate 
	//After spawn a new plate or block copy pointer to BoardActorsArray

 	ADesk* NewDesk = GetWorld()->SpawnActor<ADesk>(Desk_Blueprint, StartDeskLocation, FRotator::ZeroRotator);

	FVector NewLocation = StartPlateLocation;
	for (int32 x = 0; x < Width; x++)
	{
		for (int32 y = 0; y < Height; y++)
		{
			if (x % 2 == 0)
			{
				APlate* NewPlate = GetWorld()->SpawnActor<APlate>(Plate_Blueprint, NewLocation, FRotator::ZeroRotator);
				NewPlate->SetPlacement(x, y);
				BoardActorsArray[x][y] = NewPlate;
			}
			else if (y % 2 == 0 )
			{
				ABlock* NewBlock = GetWorld()->SpawnActor<ABlock>(Block_Blueprint, NewLocation, FRotator::ZeroRotator);
				BoardActorsArray[x][y] = NewBlock;
			}
			else
			{
				BoardActorsArray[x][y] = nullptr;
			}
			NewLocation += FVector(200.f, 0.f, 0.f);
		}
		NewLocation = StartPlateLocation + FVector(0.f, 200.f, 0.f)*(x + 1);
	}
}

bool APlatesAndBlocksGameModeBase::CheckGameCompletion()
{
	for (int i = 0; i < Width; i += 2) //Check only even or zero column
	{
		EPlateColor PlateColor = EPlateColor::Unknown;
		for (int j = 0; j < Height; j++)
		{
			if (BoardActorsArray[i][j] == nullptr)
			{ 
				return false;
			}
			if (PlateColor == EPlateColor::Unknown)
			{
				PlateColor = Cast<APlate>(BoardActorsArray[i][j])->GetPlateColor();
			}
			else if (PlateColor != Cast<APlate>(BoardActorsArray[i][j])->GetPlateColor())
			{
				return false;
			}
		}
	}
	Cast<APlateController>(GetWorld()->GetFirstPlayerController())->SetControlledPlate(nullptr);
	return true;	
}

EPlateColor APlatesAndBlocksGameModeBase::GetRandomColor()
{
	int32 ArrColorsSize = PlateColorsArr.Num();
	UE_LOG(LogTemp, Warning, TEXT("%i:"), ArrColorsSize);

	auto randNum = FMath::RandRange(0, ArrColorsSize - 1);
	UE_LOG(LogTemp, Warning, TEXT("Random element %i:"), randNum);
	
	if (randNum >= PlateColorsArr.Num())
	{
		UE_LOG(LogTemp, Warning, TEXT("Request unexisted element at PlateColorsArr %i:"), randNum);
		return EPlateColor::Unknown;
	}
	auto RetColor = PlateColorsArr[randNum];
	PlateColorsArr.RemoveAt(randNum);

	return RetColor;
}


void APlatesAndBlocksGameModeBase::UpdateBoardActorsArray(int32 x, int32 y, AActor* Actor)
{
	BoardActorsArray[x][y] = Actor;
}

bool APlatesAndBlocksGameModeBase::IsPlaceFreeAndCorrect(int32 x, int32 y)
{
	if (x >= 0 && x < Width && y >= 0 && y < Height)
	{
		if (BoardActorsArray[x][y] == nullptr)
			return true;
	}
	return false;
}

