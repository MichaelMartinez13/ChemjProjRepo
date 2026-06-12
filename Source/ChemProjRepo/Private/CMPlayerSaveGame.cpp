// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/Player/CMPlayerState.h"
#include "CMPlayerSaveGame.h"


FPlayerSaveData* UCMPlayerSaveGame::GetPlayerData(ACMPlayerState* PlayerState)
{
	check(PlayerState);
	
	// UObjects don't have access to UWorld, so we grab it via PlayerState instead
	if (PlayerState->GetWorld()->IsPlayInEditor()) 
	{
		//UE_LOGFMT(LogGame, Log, "During PIE, we can not use PlayerID to retrieve player data.");
		if (SavedPlayerData.IsValidIndex(0))
		{
			return &SavedPlayerData[0];
		}

		return nullptr;
	
	}

	FString PlayerID = PlayerState->GetUniqueId().ToString();
	
	/*
	Find by predicate is a function used to locate an element in an array that matches a specific condition defined by a lambda function.
	In this case, we are looking for a FPlayerSaveData element in the SavedPlayerData array where the PlayerID matches the PlayerID of the given PlayerState. 
	The lambda function takes a FPlayerSaveData element as input and returns true if its PlayerID matches the PlayerID we are looking for, and false otherwise.
	If a matching element is found, it is returned as a pointer; if no match is found, nullptr is returned.
	*/
	return SavedPlayerData.FindByPredicate([&](const FPlayerSaveData& Data)
	{
		return Data.PlayerID == PlayerID;
	});

}
