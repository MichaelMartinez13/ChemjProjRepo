// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CMBaseShippableProduct.generated.h"




class UBoxComponent;
class UStaticMeshComponent;




UCLASS()
class CHEMPROJREPO_API ACMBaseShippableProduct : public AActor
{
	GENERATED_BODY()

public:
	ACMBaseShippableProduct();

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr <UBoxComponent> BoxCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr <UStaticMeshComponent> StaticMesh;

	// Determines the direction the product moves in
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shipping")
	bool ShipOut = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shipping")
	float SellingPoint = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shipping")
	int32 Quantity = 1;
};