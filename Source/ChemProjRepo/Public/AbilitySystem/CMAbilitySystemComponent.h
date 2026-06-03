// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "CMAbilitySystemComponent.generated.h"

UCLASS()
class CHEMPROJREPO_API UCMAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCMAbilitySystemComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	
		
};
