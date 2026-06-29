// Fill out your copyright notice in the Description page of Project Settings.


#include "ConveyorSystem/CMBaseShippableProduct.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"


ACMBaseShippableProduct::ACMBaseShippableProduct() {
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BaseCollision"));
	SetRootComponent(BoxCollision);

	BoxCollision->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));
	BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BoxCollision->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
	BoxCollision->SetCollisionResponseToAllChannels(ECR_Block);
	BoxCollision->SetGenerateOverlapEvents(true);
	BoxCollision->SetSimulatePhysics(true);
	BoxCollision->SetMassOverrideInKg(NAME_None, 10.0f, true);

	BoxCollision->BodyInstance.bLockXRotation = true;
	BoxCollision->BodyInstance.bLockYRotation = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseStaticMesh"));
	StaticMesh->SetupAttachment(BoxCollision);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}