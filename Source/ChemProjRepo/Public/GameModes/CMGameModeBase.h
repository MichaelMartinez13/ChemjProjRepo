// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CMGameModeBase.generated.h"

/**
 * 
 */
class UCMPlayerSaveGame; 

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSaveGameSignature, class UCMPlayerSaveGame*, SaveObject);

UCLASS()
class CHEMPROJREPO_API ACMGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public: //PROPERTIES
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> LoadingScreenWidget; 

	UPROPERTY(BlueprintAssignable)
	FOnSaveGameSignature OnSaveGameLoaded;

	UPROPERTY(BlueprintAssignable)
	FOnSaveGameSignature OnSaveGameWritten;

protected:
	UPROPERTY()
	FTimerHandle LoadCheckTimer;

	UPROPERTY()
	TObjectPtr<UUserWidget> ActiveLoadingScreen = nullptr;
	
	UPROPERTY(Transient)
	TObjectPtr<UCMPlayerSaveGame> CurrentSaveGame;

public: //FUNCTIONS

	virtual void BeginPlay() override;

	virtual void Logout(AController* PlayerExit) override;

	//This logs to the engine wether the game is ending or not. 
	// If it is, it will write the save game data to disk.
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	//This function is called when a new player joins the game. 
	//It is responsible for initializing the player's state and loading their save data.
	//virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;
	
	void CheckIfGameReady();

	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	void WriteSaveGame();
	
	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	void LoadSaveGame();
	
	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	void DeleteSaveGame();

	//virtual void HandleStartingNewPlayer_Implementation(APlayerController* Player) override;

};
