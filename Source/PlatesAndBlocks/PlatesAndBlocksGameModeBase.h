// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlatesAndBlocksGameModeBase.generated.h"

class APlate;
class ABlock;
class ADesk;
class AColumnColor;

/**
 * 
 */

UENUM()
enum class EActorsColor : uint8
{
	Blue,
	Yellow,
	Red,
	Unknown
};

UCLASS()
class PLATESANDBLOCKS_API APlatesAndBlocksGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APlatesAndBlocksGameModeBase();

	//Check is Place free for plate move and exist in array
	bool IsPlaceFreeAndCorrect(int32 x, int32 y); 

	//Method for refresh BoardActorsArray after change position of figures on the board
	void UpdateBoardActorsArray(int32 x, int32 y, AActor* Actor); 

	//Method calling every plate move to check columns
	UFUNCTION(BlueprintCallable, Category = "Control")
	bool CheckGameCompletion(); 

	//Return to Plate Random color from PlateColorsArr for randomization our game and after that erase it from array
	EActorsColor GetRandomPlateColor(); 

	//Return to Plate Random color from PlateColorsArr for randomization our game and after that erase it from array
	EActorsColor GetRandomColumnColor();

	//Return to Plate Random color from PlateColorsArr for randomization our game and after that erase it from array
	EActorsColor GetRandomColorfromArray(TArray<EActorsColor> &ColorsArray);
	
protected:
	virtual void BeginPlay() override;

private:
	//Get Number of each color plates and create 2 color array (Column, Plate)
	void InitializeColorArrays();

	//Spawn Desk objects on the screen
	void SpawnDesk();

	//Spawn ColumnColor objects on the screen
	//And fill ColumnColorActorsArray by column color pointers
	void SpawnColumnColors();

	//Spawn ColumnColor objects on the screen
	//And fill BoardActorsArray by plate and blocks pointers
	void SpawnPlatesAndBlocks();

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 QtyEachColorPlates = 5;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<APlate> Plate_Blueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<ABlock> Block_Blueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<ADesk> Desk_Blueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AColumnColor> ColumnColor_Blueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	FVector StartDeskLocation = FVector(0.f, 0.f, 15.f);
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	FVector StartPlateLocation = FVector(800.f, 0.f, 40.f);
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	FVector StartColumnColorLocation = FVector(1200.f, 0.f, 40.f);

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 Width = 5;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 Height = 5;

	FVector ShiftWidth = FVector(0.f, 200.f, 0.f);

	// minus because x vector on the screen and in BoardActorsArray is the opposite directions
	FVector ShiftHeight = FVector(-200.f, 0.f, 0.f); 

	//Array for access to Plate actors and get Color
	AActor*** BoardActorsArray;
	//Array for access to ColumnColor actors and get Color
	AActor** ColumnColorActorsArray;

	//Array for initial colorize plates
	TArray<EActorsColor> PlateColorsArr;
	//Array for initial colorize columnColors
	TArray<EActorsColor> ColumnColorsArr;
};
