// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "CMAttributeChangedEvents.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FAttributeChangedEvent, UAttributeSet*, AttributeSet, float, OldValue, float, NewValue);
/*
This class is meant to be used as a base class for AttributeSets that want to have BlueprintAssignable events for when attributes change. 
It is not meant to be used as a base class for AttributeSets that want to have attributes, 
but rather as a component that can be added to an AttributeSet that wants this functionality. 
This is because the events in this class are not meant to be called directly, 
but rather through the PostAttributeChange function in the AttributeSet.
This allows for the events to be called whenever an attribute changes, 
regardless of how it changes (e.g. through a GameplayEffect, through direct modification, etc.). 
 */
UCLASS()
class CHEMPROJREPO_API UCMAttributeChangedEvents : public UAttributeSet
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FAttributeChangedEvent OnPointsChanged;




};