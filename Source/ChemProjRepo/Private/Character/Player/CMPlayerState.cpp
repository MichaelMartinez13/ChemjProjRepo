// Fill out your copyright notice in the Description page of Project Settings.
#include "Character/Player/CMPlayerState.h"
#include "CMPlayerSaveGame.h"

//#include "../../../../../../../../../../Program Files/Epic Games/UE_5.6/Engine/Plugins/Enterprise/DataprepEditor/Source/DataprepEditor/Private/DataprepSnapshot.cpp"

ACMPlayerState::ACMPlayerState()
{

	NetUpdateFrequency = 100.f;

	ASC = CreateDefaultSubobject<UCMAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	PointAttributeSet = CreateDefaultSubobject<UCMPointAttributeSet>(TEXT("PointAttributeSet"));
	ASC->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}

UAbilitySystemComponent* ACMPlayerState::GetAbilitySystemComponent() const
{
	return ASC;
}
void ACMPlayerState::SavePlayerState(UCMPlayerSaveGame* SaveGame)
{
	if (SaveGame)
	{
		//Gather all the data of the player 
		FPlayerSaveData SaveData; 
		SaveData.Points = PointAttributeSet->GetBasePoints();
	
		//Store as FString(This is for steam, so I would not look into this too much).
		SaveData.PlayerID = GetUniqueId().ToString();
	
		if (APawn* MyPawn = GetPawn()) 
		{
			SaveData.Location = MyPawn->GetActorLocation();
			SaveData.Rotation = MyPawn->GetActorRotation();
			SaveData.bResumeAtTransform = true;
		}
		
		SaveGame->SavedPlayerData.Add(SaveData);
	}

}

void ACMPlayerState::LoadPlayerState(UCMPlayerSaveGame* SaveGame)
{
	if (SaveGame) 
	{
		FPlayerSaveData* FoundData = SaveGame->GetPlayerData(this);
		if (FoundData) 
		{
			//Set the base points to the AttributeSet. 
			PointAttributeSet->SetBasePoints(FoundData->Points);
		}
		else
		{
			UE_LOG(LogTemp,Warning, TEXT("No player data found for this player state."));
		}
	}

}
/*
void ACMPlayerState::HandleStartingNewPlayer_Implementation(ACMPlayerController* PlayerController)
{
	ACMPlayerState* PS = PlayerController->GetPlayerState<ACMPlayerState>();
}
*/





/*
void ACMPlayerState::Save(FActorSaveData& SaveData)
{
	//Preparing memory writer and archive for serialization
	//FMemoryWriter MemWriter(SaveData.ByteData);
	//FObjectAndNameAsStringProxyArchive Ar(MemWriter, true);
	//Ar.ArIsSaveGame = true;

	//Create a hashmap for storing values 
	//TMap<FString, float> SavedAttributes; 
	//Ar << SavedAttributes;
	//SavedAttributes.Add(PointAttributeSet->GetBasePoints().GetName(), PointAttributeSet->GetBasePoints());
}

void ACMPlayerState::RestoreSave(FActorSaveData& SaveData)
{
}
*/