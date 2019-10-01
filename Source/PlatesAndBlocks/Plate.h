// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Plate.generated.h"

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
	void SetPlateColor(EPlateColor Color);
	void SetPlacement(int32 x, int32 y);
	PlatePosition GetPlacement();

	EPlateColor GetPlateColor();

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
	
private:
	PlatePosition PlatePos;
};
