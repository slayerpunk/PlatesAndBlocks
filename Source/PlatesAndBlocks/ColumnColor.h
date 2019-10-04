// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PlatesAndBlocksGameModeBase.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ColumnColor.generated.h"

UCLASS()
class PLATESANDBLOCKS_API AColumnColor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AColumnColor();

	//Return Column Color
	EActorsColor GetColumnColor();

	//Event method begin SetMaterial method at Blueprint
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void RefreshColor();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Bounding with material instance at Blueprint
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EActorsColor ColumnColor = EActorsColor::Red;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	APlatesAndBlocksGameModeBase* GameMode;
};
