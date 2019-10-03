// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Plate.generated.h"

class APlatesAndBlocksGameModeBase;

UENUM()
enum class EPlateColor : uint8
{
	Blue,
	Yellow,
	Red,
	Unknown
};

struct PlatePosition
{
	int32 x;
	int32 y;
};

UCLASS()
class PLATESANDBLOCKS_API APlate : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlate();

	//Set start placement after spawn with coordinates of BoardActorsArray
	void SetPlacement(int32 x, int32 y);

	//Return Plate Location on the board
	PlatePosition GetPlacement(); 

	//Return Plate Color
	EPlateColor GetPlateColor(); 

	//Event method begin SetMaterial method at Blueprint
 	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
 	void RefreshColor();
		
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Called by Plate controller on every move input (W,A,S,D)
	void Move(FVector Shift, int32 add_x, int32 add_y);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;

	//Bounding with material instance at Blueprint
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EPlateColor PlateColor = EPlateColor::Red;

private:	

	APlatesAndBlocksGameModeBase* GameMode;

	PlatePosition PlatePos;

	//Multiply for count shift plate after move, equal to length of the Plate side
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 ShiftMultiply = 200;
};
