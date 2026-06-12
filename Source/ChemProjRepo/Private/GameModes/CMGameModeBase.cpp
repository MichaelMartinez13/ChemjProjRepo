// Fill out your copyright notice in the Description page of Project Settings.

#include "Blueprint/UserWidget.h"
#include "GameModes/CMGameModeBase.h"
#include "GameState/CMGameStateBase.h"
#include "Character/Player/CMPlayerState.h"
#include "GameModes/CMGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "CMPlayerSaveGame.h"

void ACMGameModeBase::BeginPlay()
{
	Super::BeginPlay(); 
	GetWorld()->GetTimerManager().SetTimer(LoadCheckTimer, this, &ACMGameModeBase::CheckIfGameReady, 0.1f, true);
	if (IsValid(LoadingScreenWidget)) 
	{
		ActiveLoadingScreen = CreateWidget<UUserWidget>(GetWorld(), LoadingScreenWidget);
		if (IsValid(ActiveLoadingScreen))
		{
		
			ActiveLoadingScreen->AddToViewport();
		}
	}


}

void ACMGameModeBase::CheckIfGameReady()
{
	ACMGameStateBase* PlayerGameState = Cast<ACMGameStateBase>(GameState);
	if (IsValid(PlayerGameState))
	{
		if (PlayerGameState->AreAllAssetsLoaded())
		{
			GetWorld()->GetTimerManager().ClearTimer(LoadCheckTimer);
			PlayerGameState->SetGameReady();

			if (IsValid(ActiveLoadingScreen)) 
			{
				ActiveLoadingScreen->RemoveFromParent();
				ActiveLoadingScreen = nullptr;
			}
		}
	
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("Player IS NOT VALID FIX THIS NOW"))
	}

}
void ACMGameModeBase::WriteSaveGame()
{
	//Clear the arrays 
	CurrentSaveGame->SavedPlayerData.Empty();
	CurrentSaveGame->SavedActorData.Empty();

	AGameStateBase* PlayerGameState = GetWorld()->GetGameState();

	if (!IsValid(PlayerGameState)) return;

	for (int32 i = 0; i < PlayerGameState->PlayerArray.Num(); i++) 
	{
		ACMPlayerState* CMPlayerState = CastChecked<ACMPlayerState>(PlayerGameState->PlayerArray[i]);
		if (IsValid(CMPlayerState)) 
		{
			CMPlayerState->SavePlayerState(CurrentSaveGame);
			break;
			
		}
	}

	UGameplayStatics::SaveGameToSlot(CurrentSaveGame, "PlayerSlot", 0);

	OnSaveGameWritten.Broadcast(CurrentSaveGame);
}
void ACMGameModeBase::LoadSaveGame()
{
	if (UGameplayStatics::DoesSaveGameExist("PlayerSlot", 0)) 
	{
		if (!IsValid(CurrentSaveGame)) 
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to recall save slot"));
			return;
		}
		UE_LOG(LogTemp, Log, TEXT("Loaded Save Data"));
		OnSaveGameLoaded.Broadcast(CurrentSaveGame);
	}
	else 
	{
		CurrentSaveGame = CastChecked<UCMPlayerSaveGame>(UGameplayStatics::CreateSaveGameObject(UCMPlayerSaveGame::StaticClass()));

		UE_LOG(LogTemp, Log, TEXT("Created New Save game data!"));
	}
	
}
//void ACMGameModeBase::HandleStartingNewPlayer_Implementation(APlayerController* Player)
//{
	//ACMPlayerState* PlayerState = Player->GetPlayerState<ACMPlayerState>();
	//if (IsValid(PlayerState))
	//{
		//PlayerState->LoadPlayerState(CurrentSaveGame);
	//}
//}
