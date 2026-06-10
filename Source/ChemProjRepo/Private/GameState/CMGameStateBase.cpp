// Fill out your copyright notice in the Description page of Project Settings.


#include "GameState/CMGameStateBase.h"

ACMGameStateBase::ACMGameStateBase()
{

}

void ACMGameStateBase::SetGameReady()
{
	if (bIsGameReady) return;
	bIsGameReady = true;
	GameReadyEvent.Broadcast();
}

void ACMGameStateBase::RegisterLoad()
{
	++AssetsToLoad;

}

void ACMGameStateBase::MarkLoadComplete()
{
	--AssetsToLoad;
	AssetsToLoad = FMath::Max(AssetsToLoad, 0);
	if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Game is loaded!")); }

}
