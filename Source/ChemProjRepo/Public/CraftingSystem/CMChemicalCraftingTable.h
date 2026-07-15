// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"
#include "Components/WidgetComponent.h"
#include "CMChemicalCraftingTable.generated.h"

UCLASS()
class CHEMPROJREPO_API ACMChemicalCraftingTable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACMChemicalCraftingTable();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	TObjectPtr<UCameraComponent> Camera;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	TObjectPtr<UCameraComponent> PlayerCamera;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> ChemicalCraftingTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TObjectPtr<UWidgetComponent> CraftingWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IsWorking")
	bool bIsStarted;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
