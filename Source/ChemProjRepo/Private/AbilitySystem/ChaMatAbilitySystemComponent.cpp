// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ChaMatAbilitySystemComponent.h"

UChaMatAbilitySystemComponent::UChaMatAbilitySystemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicated(true);
}

void UChaMatAbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}