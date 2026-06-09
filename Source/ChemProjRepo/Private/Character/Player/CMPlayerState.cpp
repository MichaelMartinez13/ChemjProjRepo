// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/Player/CMPlayerState.h"
//#include "../../../../../../../../../../Program Files/Epic Games/UE_5.6/Engine/Plugins/Enterprise/DataprepEditor/Source/DataprepEditor/Private/DataprepSnapshot.cpp"

class FActorSaveData;
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