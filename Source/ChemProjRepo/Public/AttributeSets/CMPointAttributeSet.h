// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet/CMAttributeChangedEvents.h"
#include "CMPointAttributeSet.generated.h"

//Macro to create accessor for attributes
/*Accessors AKA getter methods, are methods in OOP
that allow you to retrieve private or protected instance variables without directly accessing them 
this is opposite of setters/mutators */
#define ATTRIBUTE_ACCESSORS(ClassName,PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)



/**
 * 
 */
UCLASS()
class CHEMPROJREPO_API UCMPointAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public: 
	UCMPointAttributeSet();

	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

public:

	//Temporary buffs are used for CurrentValue, for example a sprint boost that only last for 5 seconds.
	UPROPERTY()
	FGameplayAttributeData CurrentPoints;
	ATTRIBUTE_ACCESSORS(UCMPointAttributeSet, CurrentPoints)

	//BaseValue is used for permanent changes, for example a level up that increase max health by 10.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FGameplayAttributeData BasePoints;
	ATTRIBUTE_ACCESSORS(UCMPointAttributeSet, BasePoints)

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FGameplayAttributeData MaxPoints;
	ATTRIBUTE_ACCESSORS(UCMPointAttributeSet, MaxPoints)

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FGameplayAttributeData PointModifier; 
	ATTRIBUTE_ACCESSORS(UCMPointAttributeSet, PointModifier)

	UPROPERTY(BlueprintAssignable)
	FAttributeChangedEvent OnPointsChanged; 
};
