// Fill out your copyright notice in the Description page of Project Settings.


#include "ColumnColor.h"

// Sets default values
AColumnColor::AColumnColor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AColumnColor::BeginPlay()
{
	Super::BeginPlay();
	GameMode = Cast<APlatesAndBlocksGameModeBase>(GetWorld()->GetAuthGameMode());

	ColumnColor = GameMode->GetRandomColumnColor();
	RefreshColor();
}

// Called every frame
void AColumnColor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

EActorsColor AColumnColor::GetColumnColor()
{
	return ColumnColor;
}
