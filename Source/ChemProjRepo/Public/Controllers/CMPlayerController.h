// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Controller.h"
#include "CMPlayerSaveGame.h"
#include "Character/CMCharacterBase.h"
#include "Character/Player/CMPlayerState.h"
#include "CMPlayerController.generated.h"



/**
 * 
 */
UCLASS()
class CHEMPROJREPO_API ACMPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	UFUNCTION()
	void SaveGameData();

	UFUNCTION()
	void OnGameSaved(const FString& SlotName, const int32 UserIndex, bool bSuccess);

	UFUNCTION()
	void LoadGameData();

	virtual void BeginPlay() override;
	
	UFUNCTION()
	void HandleGameReady();

private: 

public:

	UPROPERTY()
	TObjectPtr <UCMPlayerSaveGame> SaveInstance;
	
	UPROPERTY()
	TObjectPtr <UCMPlayerSaveGame> LoadedInstance; 
	
	UPROPERTY()
	TObjectPtr <ACMCharacterBase> PlayerCharacter; 
	
	UPROPERTY()
	TObjectPtr <ACMPlayerState> CMPlayerState; 


};
