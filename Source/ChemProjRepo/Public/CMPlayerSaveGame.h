// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "CMPlayerSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class CHEMPROJREPO_API UCMPlayerSaveGame : public USaveGame
{
	GENERATED_BODY()
	

public:
	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	FString PlayerName;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	int32 PlayerScore = 0;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	FVector PlayerLocation = FVector::ZeroVector;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	TArray<FName> InventoryItemIDs;
};
