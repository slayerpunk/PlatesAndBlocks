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
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (i == 0 || i == 2 || i == 4)
			{
				auto randNum = FMath::RandRange(0, ArrColorsSize-1);
	
				UE_LOG(LogTemp, Warning, TEXT("Random element %i:"), randNum);
				APlate* NewPlate = GetWorld()->SpawnActor<APlate>(Plate_Blueprint, NewLocation, FRotator::ZeroRotator);
				if (randNum >= PlateColorsArr.Num())
				{ 
					UE_LOG(LogTemp, Warning, TEXT("Leave with failure %i:"), i);
					return; 
				}
				NewPlate->SetPlateColor(PlateColorsArr[randNum]);
				PlateColorsArr.RemoveAt(randNum);
				ArrColorsSize--;
				NewPlate->RefreshColor();			
			}
			else if (j == 0 || j == 2 || j == 4)
			{
				ABlock* NewBlock = GetWorld()->SpawnActor<ABlock>(Block_Blueprint, NewLocation, FRotator::ZeroRotator);
			}
			NewLocation += FVector(200.f, 0.f, 0.f);
		}
		NewLocation = StartLocation + FVector(0.f, 200.f, 0.f)*(i+1);
	}
	

}

// Called every frame
void ADesk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

