// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlateController.generated.h"

class APlatesAndBlocksGameModeBase;
class APlate;
class ADesk;
/**
 * 
 */
UCLASS()
class PLATESANDBLOCKS_API APlateController : public APlayerController
{
	GENERATED_BODY()

public:

	//Return Poiunter of controlled Plate at this moment
	UFUNCTION(BlueprintCallable, Category = "Setup")
	APlate* GetControlledPlate();

	//Change controlling Plate at BP 
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetControlledPlate(APlate* platePawn);

	//Method calling from Binding Action in Game then call move method at ControlledPlate if it is exist
	UFUNCTION(BlueprintCallable, Category = "Control")
	void MovePlateUp();		

	//Method calling from Binding Action in Game then call move method at ControlledPlate if it is exist
	UFUNCTION(BlueprintCallable, Category = "Control")
	void MovePlateDown();		

	//Method calling from Binding Action in Game then call move method at ControlledPlate if it is exist
	UFUNCTION(BlueprintCallable, Category = "Control")
	void MovePlateLeft();		

	//Method calling from Binding Action in Game then call move method at ControlledPlate if it is exist
	UFUNCTION(BlueprintCallable, Category = "Control")
	void MovePlateRight();		

protected: 

	virtual void BeginPlay() override;

private:
	
	APlatesAndBlocksGameModeBase* GameMode = nullptr;
	APlate* ControlledPlate = nullptr;

	FVector ShiftUp = { 1.0,0.0,0.0 };
	FVector ShiftDown = { -1.0,0.0,0.0 };
	FVector ShiftLeft = { 0.0,-1.0,0.0 };
	FVector ShiftRight = { 0.0,1.0,0.0 };
	
};
