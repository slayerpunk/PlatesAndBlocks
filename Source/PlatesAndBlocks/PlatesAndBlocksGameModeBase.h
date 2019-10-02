// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Plate.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlatesAndBlocksGameModeBase.generated.h"

class APlate;
class ABlock;
class ADesk;

/**
 * 
 */
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
	EPlateColor GetRandomColor(); 
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 QtyEachColorPlates = 5;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<APlate> Plate_Blueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<ABlock> Block_Blueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<ADesk> Desk_Blueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	FVector StartDeskLocation = FVector(0.f, 0.f, 15.f);
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	FVector StartPlateLocation = FVector(0.f, 0.f, 40.f);
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 Width = 5;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 Height = 5;

	AActor*** BoardActorsArray;

	bool IsPlateSeqCorrect = false;
	TArray<EPlateColor> PlateColorsArr;
};
