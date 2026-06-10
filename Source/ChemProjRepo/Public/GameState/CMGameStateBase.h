// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "CMGameStateBase.generated.h"

DECLARE_EVENT(ACMGameStateBase, FOnGameReadyEvent);


/**
 * 
 */
UCLASS()
class CHEMPROJREPO_API ACMGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
public: 

	ACMGameStateBase();

	UFUNCTION()
	void SetGameReady();

	UFUNCTION()
	void RegisterLoad();

	UFUNCTION()
	void MarkLoadComplete();

	UFUNCTION()
	bool AreAllAssetsLoaded() const { return AssetsToLoad <= 0; }

	UFUNCTION()
	int32 GetPendingAssetsToLoad() const { return AssetsToLoad; }

	FOnGameReadyEvent& OnGameReady() { return GameReadyEvent; }


protected: 

	int32 AssetsToLoad = 0;

	FOnGameReadyEvent GameReadyEvent;

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsGameReady = false;

};
