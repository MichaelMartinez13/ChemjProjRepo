// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CMChemicalCraftingTable.generated.h"

UCLASS()
class CHEMPROJREPO_API ACMChemicalCraftingTable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACMChemicalCraftingTable();

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> ChemicalCraftingTable;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
