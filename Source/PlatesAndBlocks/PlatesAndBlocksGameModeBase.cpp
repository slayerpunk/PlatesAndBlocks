// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatesAndBlocksGameModeBase.h"
#include "Block.h"
#include "PlateController.h"
#include "Desk.h"
#include "ColumnColor.h"

APlatesAndBlocksGameModeBase::APlatesAndBlocksGameModeBase()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
		
	BoardActorsArray = new AActor**[Height]; 
	for (int count = 0; count < Height; count++)
	{
		BoardActorsArray[count] = new AActor*[Width];
	}
	
	ColumnColorActorsArray = new AActor*[Width];
}
void APlatesAndBlocksGameModeBase::BeginPlay()
{
	//Initialize Color array
	Super::BeginPlay();
	
	// X and Y axes according to UE4 project system coordinate

	InitializeColorArrays();

	//At First Spawn Game Desk
	//After that begin spawn plates and block 
	//Plates Spawning at every even or zero column (start from 0)
	//Blocks Spawning at odd columns and only at even or 0 rows (start from 0)
	//A new plate at begin play calling GetRandomPlateColor Method to colorize the plate 
	//After spawn a new plate or block copy pointer to BoardActorsArray
 	
	SpawnDesk();

	SpawnColumnColors();

	SpawnPlatesAndBlocks();
}

void APlatesAndBlocksGameModeBase::InitializeColorArrays()
{
	for (int i = 0; i < QtyEachColorPlates; i++)
	{
		PlateColorsArr.Add(EActorsColor::Blue);
		PlateColorsArr.Add(EActorsColor::Yellow);
		PlateColorsArr.Add(EActorsColor::Red);
	}

	ColumnColorsArr.Add(EActorsColor::Blue);
	ColumnColorsArr.Add(EActorsColor::Yellow);
	ColumnColorsArr.Add(EActorsColor::Red);
}

void APlatesAndBlocksGameModeBase::SpawnDesk()
{
	ADesk* NewDesk = GetWorld()->SpawnActor<ADesk>(Desk_Blueprint, StartDeskLocation, FRotator::ZeroRotator);
}

void APlatesAndBlocksGameModeBase::SpawnColumnColors()
{
	FVector NewLocation = StartColumnColorLocation;
	for (int32 y = 0; y < Width; y++)
	{
		if (y % 2 == 0) //spawn ColumnColors only at even or zero column
		{
			AColumnColor* NewColumnColor = GetWorld()->SpawnActor<AColumnColor>(ColumnColor_Blueprint, NewLocation, FRotator::ZeroRotator);

			ColumnColorActorsArray[y] = NewColumnColor;
		}
		else
		{
			ColumnColorActorsArray[y] = nullptr;
		}
		NewLocation += ShiftWidth; 
	}
}

void APlatesAndBlocksGameModeBase::SpawnPlatesAndBlocks()
{
	FVector NewLocation = StartPlateLocation;
	for (int32 y = 0; y < Width; y++)
	{
		for (int32 x = 0; x < Height; x++)
		{
			if (y % 2 == 0)
			{
				APlate* NewPlate = GetWorld()->SpawnActor<APlate>(Plate_Blueprint, NewLocation, FRotator::ZeroRotator);
				NewPlate->SetPlacement(x, y);
				BoardActorsArray[x][y] = NewPlate;
			}
			else if (x % 2 == 0)
			{
				ABlock* NewBlock = GetWorld()->SpawnActor<ABlock>(Block_Blueprint, NewLocation, FRotator::ZeroRotator);
				BoardActorsArray[x][y] = NewBlock;
			}
			else
			{
				BoardActorsArray[x][y] = nullptr;
			}
			NewLocation += ShiftHeight; 
		}
		NewLocation = StartPlateLocation + ShiftWidth*(y+1); //Start from the beginning and shift in width according column number
	}
}

EActorsColor APlatesAndBlocksGameModeBase::GetRandomPlateColor()
{
	return APlatesAndBlocksGameModeBase::GetRandomColorfromArray(PlateColorsArr);
}

EActorsColor APlatesAndBlocksGameModeBase::GetRandomColumnColor()
{
	return APlatesAndBlocksGameModeBase::GetRandomColorfromArray(ColumnColorsArr);
}

EActorsColor APlatesAndBlocksGameModeBase::GetRandomColorfromArray(TArray<EActorsColor> &ColorsArray)
{
	int32 ArrColorsSize = ColorsArray.Num();

	int32 randNum = FMath::RandRange(0, ArrColorsSize - 1);
	
	if (randNum >= ColorsArray.Num())
	{
		return EActorsColor::Unknown;
	}
	EActorsColor RetColor = ColorsArray[randNum];
	ColorsArray.RemoveAt(randNum);

	return RetColor;
}

bool APlatesAndBlocksGameModeBase::IsPlaceFreeAndCorrect(int32 x, int32 y)
{
	if (y >= 0 && y < Width && x >= 0 && x < Height)
	{
		if (BoardActorsArray[x][y] == nullptr)
			return true;
	}
	return false;
}

void APlatesAndBlocksGameModeBase::UpdateBoardActorsArray(int32 x, int32 y, AActor* Actor)
{
	BoardActorsArray[x][y] = Actor;
}

bool APlatesAndBlocksGameModeBase::CheckGameCompletion()
{
	for (int y = 0; y < Width; y += 2) //Check only even or zero column
	{
		
		EActorsColor ColumnColor = Cast<AColumnColor>(ColumnColorActorsArray[y])->GetColumnColor();
		if (!ColumnColorActorsArray[y])
		{
			return false;
		}
		for (int x = 0; x < Height; x++)
		{
			if (BoardActorsArray[x][y] == nullptr)
			{
				return false;
			}
			if (ColumnColor != Cast<APlate>(BoardActorsArray[x][y])->GetPlateColor())
			{
				return false;
			}
		}
	}
	Cast<APlateController>(GetWorld()->GetFirstPlayerController())->SetControlledPlate(nullptr);
	return true;
}