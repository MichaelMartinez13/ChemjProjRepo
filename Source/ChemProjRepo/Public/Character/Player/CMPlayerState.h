// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/CMAbilitySystemComponent.h"
#include "AttributeSets/CMPointAttributeSet.h"
#include "CMPlayerState.generated.h"

class CMPlayerSaveGame;
class ACMPlayerController;
/**
 * 
 */


UCLASS()
class CHEMPROJREPO_API ACMPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ACMPlayerState();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

/*	UFUNCTION(EditAnywhere, Category = "ASC | Attributes | Save State")
	void Save(FActorSaveData& SaveData);
	
	UFUNCTION(EditAnywhere, Category = "ASC | Attributes | Save State")
	void RestoreSave(FActorSaveData& SaveData);
	
	*/
	UFUNCTION(BlueprintCallable)
	 void SavePlayerState(UCMPlayerSaveGame* SaveGame);
	
	UFUNCTION(BlueprintCallable)
	void LoadPlayerState(UCMPlayerSaveGame* SaveGame);
	
	//UFUNCTION()
	
	

protected:
	

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ASC | Attributes")
	TObjectPtr<UCMAbilitySystemComponent> ASC;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ASC | Attributes")
	TObjectPtr <UCMPointAttributeSet> PointAttributeSet;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimationWidgets | IntroAnimation")
	bool bHasIntroPlayed;

};
