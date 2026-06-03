// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "ChaMatAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class CHEMPROJREPO_API UChaMatAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public: 

	UChaMatAbilitySystemComponent();
	
protected:
	virtual void BeginPlay() override;
};
