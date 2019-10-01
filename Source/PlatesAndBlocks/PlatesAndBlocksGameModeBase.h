// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Plate.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlatesAndBlocksGameModeBase.generated.h"

class APlate;
class ABlock;

/**
 * 
 */
UCLASS()
class PLATESANDBLOCKS_API APlatesAndBlocksGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	
	bool IsPlaceFreeAndCorrect(int32 x, int32 y);
	void SetBoard(int32 x, int32 y, AActor* Plate);
	bool IsGameCompleted();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 QtyEachColorPlates = 5;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<APlate> Plate_Blueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<ABlock> Block_Blueprint;

	static const int32 Width = 5;
	static const int32 Height = 5;
	AActor* Board[Width][Height];

	bool IsPlateSeqCorrect = false;

	TArray<EPlateColor> PlateColorsArr;
};
