// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "GameState/CMGameStateBase.h"
#include "Controllers/CMPlayerController.h"


void ACMPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ACMGameStateBase* CMGameState = GetWorld()->GetGameState<ACMGameStateBase>();
	if (CMGameState) 
	{
		if (!CMGameState->bIsGameReady) 
		{
			DisableInput(this);
			//LoadGameData();
			CMGameState->OnGameReady().AddUObject(this, &ACMPlayerController::HandleGameReady);
		}
	}
}

void ACMPlayerController::HandleGameReady()
{
	EnableInput(this);
}

void ACMPlayerController::SaveGameData()
{

	const FString SlotName = TEXT("PlayerSlot");
	const int32 UserIndex = 0;

	if (!IsValid(SaveInstance)) return;

	//Load Existing data if available, else create new
	if (UGameplayStatics::DoesSaveGameExist(SlotName, UserIndex))
	{
		SaveInstance = Cast<UCMPlayerSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, UserIndex));
	}

	if (!SaveInstance) SaveInstance = Cast<UCMPlayerSaveGame>(UGameplayStatics::CreateSaveGameObject(UCMPlayerSaveGame::StaticClass()));
	if (!IsValid(CMPlayerState)) return;
	//Transfer current game state to the SaveGame obj
	SaveInstance->PlayerName = TEXT("Chem Intern");
	SaveInstance->PlayerScore = CMPlayerState->PointAttributeSet->GetBasePoints();
	SaveInstance->PlayerLocation = GetPawn()->GetActorLocation();

	//This allows for async loading (Async is good for avoiding bloackage to the main thread)
	FAsyncSaveGameToSlotDelegate OnSaved;
	OnSaved.BindUObject(this, &ACMPlayerController::OnGameSaved);
	UGameplayStatics::AsyncSaveGameToSlot(SaveInstance, SlotName, UserIndex, OnSaved);

}


void ACMPlayerController::OnGameSaved(const FString& SlotName, const int32 UserIndex, bool bSuccess)
{
	if (bSuccess) 
	{
		UE_LOG(LogTemp, Log, TEXT("Save Succeeded: %s"), *SlotName);
	}
	else 
	{
		UE_LOG(LogTemp, Error, TEXT("Save failed: %s"), *SlotName);
	}

}

void ACMPlayerController::LoadGameData()
{
	const FString SlotName = TEXT("PlayerSlot"); 
	const int32 UserIndex = 0;

	if (!UGameplayStatics::DoesSaveGameExist(SlotName, UserIndex)) 
	{
		UE_LOG(LogTemp, Warning, TEXT("NO SAVE DATA FOUND IN SLOT: %s"), *SlotName);
		return;
	}
	LoadedInstance = Cast<UCMPlayerSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, UserIndex));
	
	//Restoring game stat from game save obj
	if (!IsValid(LoadedInstance)) return;
	//DEPRICATED for now: SetPlayerName(LoadedInstance->PlayerName);
	
	if (IsValid(CMPlayerState)) 
	{
		CMPlayerState->PointAttributeSet->SetBasePoints(SaveInstance->PlayerScore);
	}
	
	if(APawn* PlayerPawn = GetPawn())
	{
		PlayerPawn->SetActorLocation(LoadedInstance->PlayerLocation);
	}
	

}

