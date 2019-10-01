// Fill out your copyright notice in the Description page of Project Settings.


#include "Plate.h"
#include "PlatesAndBlocksGameModeBase.h"

// Sets default values
APlate::APlate()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
}

void APlate::SetPlateColor(EPlateColor Color)
{
	PlateColor = Color;
}

void APlate::SetPlacement(int32 x, int32 y)
{
	PlatePos.x = x;
	PlatePos.y = y;
}

PlatePosition APlate::GetPlacement()
{
	return PlatePos;
}

EPlateColor APlate::GetPlateColor()
{
	return PlateColor;
}

void APlate::BeginPlay()
{
	Super::BeginPlay();
	auto GameMode = Cast<APlatesAndBlocksGameModeBase>(GetWorld()->GetAuthGameMode());
		 	
	PlateColor = GameMode->GetRandomColor();
	RefreshColor();

}

// Called every frame
void APlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlate::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


