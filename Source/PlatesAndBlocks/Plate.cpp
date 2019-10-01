// Fill out your copyright notice in the Description page of Project Settings.


#include "Plate.h"
#include "PlatesAndBlocksGameModeBase.h"

// Sets default values
APlate::APlate()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//TODO make color initialization at a constructor	
}

void APlate::BeginPlay()
{
	Super::BeginPlay();
	GameMode = Cast<APlatesAndBlocksGameModeBase>(GetWorld()->GetAuthGameMode());

	PlateColor = GameMode->GetRandomColor();
	RefreshColor();
}

void APlate::SetPlacement(int32 x, int32 y)
{
	//TODO Replace Set Method
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

void APlate::Move(FVector Shift, int32 add_x, int32 add_y)
{
	if (GameMode->IsPlaceFreeAndCorrect(PlatePos.x + add_x, PlatePos.y + add_y))
	{
		GameMode->SetBoard(PlatePos.x, PlatePos.y, nullptr);
		GameMode->SetBoard(PlatePos.x + add_x, PlatePos.y + +add_y, this);
		PlatePos.x += add_x;
		PlatePos.y += add_y;
		
		SetActorLocation(GetActorLocation() + Shift*ShiftMultiply);
		GameMode->CheckGameCompletion();
	}
}


