// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/CMAbilitySystemComponent.h"

// Sets default values for this component's properties
UCMAbilitySystemComponent::UCMAbilitySystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicated(true);

	// ...
}


// Called when the game starts
void UCMAbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

