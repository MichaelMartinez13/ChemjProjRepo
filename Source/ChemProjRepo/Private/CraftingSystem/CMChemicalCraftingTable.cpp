// Fill out your copyright notice in the Description page of Project Settings.


#include "CraftingSystem/CMChemicalCraftingTable.h"
#include "Controllers/CMPlayerController.h"
#include "Character/CMCharacterBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACMChemicalCraftingTable::ACMChemicalCraftingTable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	ChemicalCraftingTable = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CraftingTable"));
	ChemicalCraftingTable->SetupAttachment(GetRootComponent());
	ChemicalCraftingTable->SetRelativeRotation(FRotator::ZeroRotator);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	CraftingWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("CraftingWidget"));
	CraftingWidget->SetupAttachment(ChemicalCraftingTable);
	
}

// Called when the game starts or when spawned
void ACMChemicalCraftingTable::BeginPlay()
{

	Super::BeginPlay();
	ACMPlayerController* PlayerController = Cast<ACMPlayerController>(UGameplayStatics::GetPlayerController(this,0));
	ACMCharacterBase* PlayerCharacter = Cast<ACMCharacterBase>(UGameplayStatics::GetPlayerCharacter(this,0));
	if (IsValid(PlayerController) && IsValid(PlayerCharacter)) 
	{
		//Might be depricated
		PlayerCamera = PlayerCharacter->FirstPersonCameraComponent;
		if(!IsValid(PlayerCamera))
		{
			UE_LOG(LogTemp, Warning, TEXT("Player Camera is not valid"))
			return;
		}
	
	}
}

// Called every frame
void ACMChemicalCraftingTable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ACMPlayerController* PlayerController = Cast<ACMPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	ACMCharacterBase* PlayerCharacter = Cast<ACMCharacterBase>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if(!IsValid(PlayerController) || !IsValid(PlayerCharacter)) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controller or Player Character is not valid"))
		return;
	}
	
	if(bIsStarted)
	{
		PlayerController->SetViewTarget(this);
	
	}
	else 
	{
		PlayerController->SetViewTarget(PlayerCharacter);
	}
}

