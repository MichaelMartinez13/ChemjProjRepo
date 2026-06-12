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

	void CheckIfGameReady();

	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	void WriteSaveGame();
	
	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	void LoadSaveGame();
	//virtual void HandleStartingNewPlayer_Implementation(APlayerController* Player) override;

};
