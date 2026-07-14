// Fill out your copyright notice in the Description page of Project Settings.


#include "CraftingSystem/CMChemicalCraftingTable.h"

// Sets default values
ACMChemicalCraftingTable::ACMChemicalCraftingTable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	ChemicalCraftingTable = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CraftingTable"));
	ChemicalCraftingTable->SetupAttachment(GetRootComponent());
	ChemicalCraftingTable->SetRelativeRotation(FRotator::ZeroRotator);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

}

// Called when the game starts or when spawned
void ACMChemicalCraftingTable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACMChemicalCraftingTable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

