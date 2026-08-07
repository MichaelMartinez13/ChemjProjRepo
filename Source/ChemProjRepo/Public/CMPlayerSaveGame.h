// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/SaveGame.h"
#include "CMPlayerSaveGame.generated.h"

class ACMPlayerState;
/**
 * 
 */
USTRUCT()
struct FPlayerSaveData
{
	GENERATED_BODY()

public:  

	//Constructor
	FPlayerSaveData() 
	{
		Points = 0;
		bHasIntroPlayed = false;
		Location = FVector::ZeroVector;
		Rotation = FRotator::ZeroRotator;
		bResumeAtTransform = true;

	}

	UPROPERTY()
	FString PlayerID;

	UPROPERTY()
	int32 Points;
	
	UPROPERTY()
	bool bHasIntroPlayed;
	
	UPROPERTY()
	FRotator Rotation; 

	UPROPERTY()
	FVector Location;

	UPROPERTY()
	bool bResumeAtTransform;


};

USTRUCT()
struct FActorSaveData
{
	GENERATED_BODY()

public:  

	UPROPERTY()
	FName ActorName;

	UPROPERTY()
	FTransform Transform;
	
	UPROPERTY()
	TArray<uint8> ByteData;


};

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
	bool bHasIntroPlayed = false;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	FVector PlayerLocation = FVector::ZeroVector;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	TArray<FName> InventoryItemIDs;

	UPROPERTY()
	TArray<FPlayerSaveData> SavedPlayerData;

	UPROPERTY()
	TMap<FName, FActorSaveData> SavedActorData;

	FPlayerSaveData* GetPlayerData(ACMPlayerState* PlayerState);
};
