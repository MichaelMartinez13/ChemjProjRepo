// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/CMPlayerState.h"

ACMPlayerState::ACMPlayerState()
{

	NetUpdateFrequency = 100.f;

	ASC = CreateDefaultSubobject<UCMAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	ASC->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}

UAbilitySystemComponent* ACMPlayerState::GetAbilitySystemComponent() const
{
	return ASC;
}
