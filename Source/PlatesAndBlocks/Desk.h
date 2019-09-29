// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Plate.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Desk.generated.h"


class APlate;
class ABlock;

UCLASS()
class PLATESANDBLOCKS_API ADesk : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADesk();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 QtyEachColorPlates = 5;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<APlate> Plate_Blueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<ABlock> Block_Blueprint;

	static const int32 Width = 5;
	static const int32 Height = 5;
	TArray<int32> Board[Width][Height];

	TArray<EPlateColor> PlateColorsArr;
};
