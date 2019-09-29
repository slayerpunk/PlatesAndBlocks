// Fill out your copyright notice in the Description page of Project Settings.


#include "Plate.h"

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

// Called when the game starts or when spawned
void APlate::BeginPlay()
{
	Super::BeginPlay();
	
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

void APlate::MoveUp()
{
	UE_LOG(LogTemp, Warning, TEXT("%s: Move Up"), *GetName());
	
}
void APlate::MoveDown()
{
	UE_LOG(LogTemp, Warning, TEXT("%s: Move Down"), *GetName());
}
void APlate::MoveLeft()
{
	UE_LOG(LogTemp, Warning, TEXT("%s: Move Left"), *GetName());
}
void APlate::MoveRight()
{
	UE_LOG(LogTemp, Warning, TEXT("%s: Move Right"), *GetName());
}
