// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeSets/CMPointAttributeSet.h"
#include "GameplayEffectExtension.h"

UCMPointAttributeSet::UCMPointAttributeSet()
{
	InitMaxPoints(999.f);
	InitBasePoints(0.f);

}

void UCMPointAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	if(Attribute == GetBasePointsAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxPoints());
	}

	//Super is used to call the parent class's implementation of the function,
	// in this case UAttributeSet's PreAttributeChange function.
	Super::PreAttributeChange(Attribute, NewValue);
	
}

void UCMPointAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);

	//PostAttributeChange is called after an attribute has been changed, and it provides the old and new values of the attribute.
	if(Attribute == GetBasePointsAttribute())
	{
		UE_LOG(LogTemp, Warning, TEXT("PostAttribtueChange: BasePoints changed from %f to %f"), OldValue, NewValue);
		OnPointsChanged.Broadcast(this, OldValue, NewValue);
	}
	//This code checks if the changed attribute is BasePoints, 
	//and if so, it logs the change and broadcasts an event to notify other parts of the system about the change in points.
	else if(Attribute == GetMaxPointsAttribute())
	{
		const float BasePointsValue = GetBasePoints();
		UE_LOG(LogTemp, Warning, TEXT("PostAttribtueChange: MaxPoints changed from %f to %f"), OldValue, NewValue);
		OnPointsChanged.Broadcast(this, BasePointsValue, BasePointsValue);
	}
}

void UCMPointAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	FString AttributeName = Data.EvaluatedData.Attribute.IsValid() ? Data.EvaluatedData.Attribute.GetName() : FString(TEXT("Invalid Attribute"));
	UE_LOG(LogTemp, Warning, TEXT("PostGameplayEffectExecute: Attribute is %s, PointModifier is %f, BasePoints are %f, MaxPoints are %f"), *AttributeName, GetPointModifier(), GetBasePoints(), GetMaxPoints());
	if(Data.EvaluatedData.Attribute == GetPointModifierAttribute())
	{
		const float PointModifierValue = GetPointModifier();
		float OldPointsValue = GetBasePoints();
		const float MaxPointsValue = GetMaxPoints();

		const float NewPointsValue = FMath::Clamp(OldPointsValue + PointModifierValue, 0.f, MaxPointsValue);

		UE_LOG(LogTemp, Warning, TEXT("PostGameplayEffectExecute: BasePoints changed to %f"), OldPointsValue);
		//OnPointsChanged.Broadcast(this, OldPointsValue, OldPointsValue);

		if(OldPointsValue != NewPointsValue)
		{
			SetBasePoints(NewPointsValue);
			UE_LOG(LogTemp, Warning, TEXT("PostGameplayEffectExecute: BasePoints changed to %f"), NewPointsValue);
			//OnPointsChanged.Broadcast(this, OldPointsValue, NewPointsValue);
		}
		SetPointModifier(0.f);
	}
}
