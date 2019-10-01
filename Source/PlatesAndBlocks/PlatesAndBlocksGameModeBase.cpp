// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatesAndBlocksGameModeBase.h"
#include "Block.h"
#include "PlateController.h"
#include "Desk.h"

void APlatesAndBlocksGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	for (int i = 0; i < QtyEachColorPlates; i++)
	{
		PlateColorsArr.Add(EPlateColor::Blue);
		PlateColorsArr.Add(EPlateColor::Yellow);
		PlateColorsArr.Add(EPlateColor::Red);
	}
//	int32 ArrColorsSize = PlateColorsArr.Num();
//	UE_LOG(LogTemp, Warning, TEXT("%i:"), ArrColorsSize);
	//Make a location for the new actor to spawn at (300 units above this actor)  

	ADesk* NewDesk = GetWorld()->SpawnActor<ADesk>(Desk_Blueprint, StartDeskLocation, FRotator::ZeroRotator);

	FVector NewLocation = StartPlateLocation;
	for (int32 x = 0; x < Width; x++)
	{
		for (int32 y = 0; y < Height; y++)
		{
			if (x == 0 || x == 2 || x == 4)
			{

				APlate* NewPlate = GetWorld()->SpawnActor<APlate>(Plate_Blueprint, NewLocation, FRotator::ZeroRotator);

				NewPlate->SetPlacement(x, y);
				Board[x][y] = NewPlate;
			}
			else if (y == 0 || y == 2 || y == 4)
			{
				ABlock* NewBlock = GetWorld()->SpawnActor<ABlock>(Block_Blueprint, NewLocation, FRotator::ZeroRotator);
				Board[x][y] = NewBlock;
			}
			else
			{
				Board[x][y] = nullptr;
			}
			NewLocation += FVector(200.f, 0.f, 0.f);
		}
		NewLocation = StartPlateLocation + FVector(0.f, 200.f, 0.f)*(x + 1);
	}
}

void APlatesAndBlocksGameModeBase::CheckGameCompletion()
{
	//TODO Something nice
	IsPlateSeqCorrect = false;
	for (int i = 0; i < Width; i += 2)
	{
		EPlateColor PlateColor = EPlateColor::Unknown;
		for (int j = 0; j < Height; j++)
		{
			if (Board[i][j] == nullptr)
			{ 
				IsPlateSeqCorrect = false;
				break; 
			}
			if (PlateColor == EPlateColor::Unknown)
			{
				PlateColor = Cast<APlate>(Board[i][j])->GetPlateColor();
			}
			else if (PlateColor == Cast<APlate>(Board[i][j])->GetPlateColor())
			{
				IsPlateSeqCorrect = true;
			}
			else
			{
				IsPlateSeqCorrect = false;
				break;
			}
		}
		if (!IsPlateSeqCorrect)
		{
			UE_LOG(LogTemp, Warning, TEXT("Game not completed yet."));
			break;
		}
	}
	if (IsPlateSeqCorrect)
	{
		UE_LOG(LogTemp, Warning, TEXT("Game Completed! Congratulation!"));
		IsGameCompleted = true;
	}
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


void APlatesAndBlocksGameModeBase::SetBoard(int32 x, int32 y, AActor* Plate)
{
	Board[x][y] = Plate;
}

bool APlatesAndBlocksGameModeBase::IsPlaceFreeAndCorrect(int32 x, int32 y)
{
	if (x >= 0 && x < Width && y >= 0 && y < Height)
	{
		if (Board[x][y] == nullptr)
			return true;
	}
	return false;
}

bool APlatesAndBlocksGameModeBase::GetGameState()
{
	if (IsGameCompleted)
	{
		Cast<APlateController>(GetWorld()->GetFirstPlayerController())->SetControlledPlate(nullptr);
	}
	return IsGameCompleted;
}
