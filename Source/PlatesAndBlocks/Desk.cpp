// Fill out your copyright notice in the Description page of Project Settings.

#include "Desk.h"
#include "Block.h"
#include "Math\RandomStream.h"

// Sets default values
ADesk::ADesk()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

bool ADesk::IsPlaceFreeAndCorrect(int32 x, int32 y)
{
	if ( x >= 0 && x < Width && y >= 0 && y < Height )
	{
		if (Board[x][y] == 0)
			return true;
	}
	return false;
}

void ADesk::SetBoard(int32 x, int32 y, int32 state)
{
	Board[x][y] = state;
}

// Called when the game starts or when spawned
void ADesk::BeginPlay()
{
	Super::BeginPlay();
	for (int i =0; i < QtyEachColorPlates; i++)
	{
		PlateColorsArr.Add(EPlateColor::Blue);
 		PlateColorsArr.Add(EPlateColor::Yellow);
 		PlateColorsArr.Add(EPlateColor::Red);		
	}
	int32 ArrColorsSize = PlateColorsArr.Num();
	UE_LOG(LogTemp, Warning, TEXT("%i:"), ArrColorsSize);
	//Make a location for the new actor to spawn at (300 units above this actor)  
	FVector StartLocation = GetActorLocation() + FVector(0.f, 0.f, 16.f);
	FVector NewLocation = StartLocation;
	for (int32 x = 0; x < Width; x++)
	{
		for (int32 y = 0; y < Height; y++)
		{
			if (x == 0 || x == 2 || x == 4)
			{
				auto randNum = FMath::RandRange(0, ArrColorsSize-1);
	
				UE_LOG(LogTemp, Warning, TEXT("Random element %i:"), randNum);
				APlate* NewPlate = GetWorld()->SpawnActor<APlate>(Plate_Blueprint, NewLocation, FRotator::ZeroRotator);
				if (randNum >= PlateColorsArr.Num())
				{ 
					UE_LOG(LogTemp, Warning, TEXT("Request unexisted element at PlateColorsArr %i:"), randNum);
					return; 
				}
				NewPlate->SetPlateColor(PlateColorsArr[randNum]);
				PlateColorsArr.RemoveAt(randNum);
				ArrColorsSize--;
				NewPlate->RefreshColor();	
				NewPlate->SetPlacement(x, y);
				//TODO check normal initialization of two dimensional array
				Board[x][y] = 1;
			}
			else if (y == 0 || y == 2 || y == 4)
			{
				ABlock* NewBlock = GetWorld()->SpawnActor<ABlock>(Block_Blueprint, NewLocation, FRotator::ZeroRotator);
				Board[x][y] = 1;
			}
			else
			{
				Board[x][y] = 0;
			}
			NewLocation += FVector(200.f, 0.f, 0.f);
		}
		NewLocation = StartLocation + FVector(0.f, 200.f, 0.f)*(x+1);
	}
	

}

// Called every frame
void ADesk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

