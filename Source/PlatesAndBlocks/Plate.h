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
	void SetPlacement(int32 x, int32 y);

	PlatePosition GetPlacement(); //Return Plate Location on the board
	EPlateColor GetPlateColor(); //Return Plate Color

 	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
 	void RefreshColor();

protected:
	virtual void BeginPlay() override;
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EPlateColor PlateColor = EPlateColor::Red;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void Move(FVector Shift, int32 add_x, int32 add_y);
private:
	
	APlatesAndBlocksGameModeBase* GameMode;
	PlatePosition PlatePos;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 ShiftMultiply = 200;
};
