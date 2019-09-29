// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlateController.generated.h"

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

	UFUNCTION(BlueprintCallable, Category = "Setup")
	APlate* GetControlledPlate();

	UFUNCTION(BlueprintCallable, Category = "Control")
	void MovePlateUp();
	UFUNCTION(BlueprintCallable, Category = "Control")
	void MovePlateDown();
	UFUNCTION(BlueprintCallable, Category = "Control")
	void MovePlateLeft();
	UFUNCTION(BlueprintCallable, Category = "Control")
	void MovePlateRight();

protected: 

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetControlledPlate(APlate* platePawn);
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetDesk(ADesk* Desk);
private:
	
	APlate* ControlledPlate = nullptr;
	ADesk* Desk = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 ShiftMultiply = 200;

	FVector ShiftUp = { 1.0,0.0,0.0 };
	FVector ShiftDown = { -1.0,0.0,0.0 };
	FVector ShiftLeft = { 0.0,-1.0,0.0 };
	FVector ShiftRight = { 0.0,1.0,0.0 };
};
