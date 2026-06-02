// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/ArrowComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "InputTriggers.h"
#include "Camera/CameraComponent.h"
#include "CMCharacterBase.generated.h"



class UInputMappingContext;
class UInputAction; 
class UInputComponent;

UCLASS()
class CHEMPROJREPO_API ACMCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACMCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> FirstPersonContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> PlayerMove;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void Move(const FInputActionValue& Value);
	
	UFUNCTION()
	void Look(const FInputActionValue& Value);
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Chained|Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UArrowComponent> PlayerArrow;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input | Camera")
	TObjectPtr<USkeletalMeshComponent> PlayerMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input | Camera")
	TObjectPtr<UCameraComponent> FirstPersonCameraComponent;

	UPROPERTY(EditAnywhere, Category = "Input | Camera")
	FVector FirstPersonCameraOffset = FVector(2.8f, 5.9f, 0.0f);

	UPROPERTY(EditAnywhere, Category = "Animation")
	TObjectPtr<UAnimBlueprint> FirstPersonAnimBP;
	UPROPERTY(EditAnywhere, Category = "Input | Camera")
	float FirstPersonFOV = 70.f;

	UPROPERTY(EditAnywhere, Category = "Input | Camera")
	float FirstPersonViewScale = 0.6f;

};
