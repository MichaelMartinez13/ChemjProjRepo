// Fill out your copyright notice in the Description page of Project Settings.

#include "GameModes/CMGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "GameState/CMGameStateBase.h"
#include "Character/Player/CMPlayerState.h"
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
			CurrentSaveGame = CastChecked<UCMPlayerSaveGame>(UGameplayStatics::CreateSaveGameObject(UCMPlayerSaveGame::StaticClass()));
			ActiveLoadingScreen->AddToViewport();
		}
	}


}

void ACMGameModeBase::Logout(AController* PlayerExit)
{
	Super::Logout(PlayerExit);

	WriteSaveGame();
}

void ACMGameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (EndPlayReason == EEndPlayReason::Quit)
	{
		WriteSaveGame();
	}

	Super::EndPlay(EndPlayReason);
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
	if (IsValid(CurrentSaveGame)) 
	{
		CurrentSaveGame->SavedPlayerData.Empty();
		CurrentSaveGame->SavedActorData.Empty();
	}
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
		USaveGame* LoadedGame = UGameplayStatics::LoadGameFromSlot("PlayerSlot", 0);
		CurrentSaveGame = CastChecked<UCMPlayerSaveGame>(LoadedGame);
		
		if (!IsValid(CurrentSaveGame)) 
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to recall save slot"));
			return;
		}
		UE_LOG(LogTemp, Log, TEXT("Loaded Save Data"));
		
		AGameStateBase* PlayerGameState = GetWorld()->GetGameState();

		if (!IsValid(PlayerGameState)) return;

		for (int32 i = 0; i < PlayerGameState->PlayerArray.Num(); i++)
		{
			ACMPlayerState* CMPlayerState = CastChecked<ACMPlayerState>(PlayerGameState->PlayerArray[i]);
			if (IsValid(CMPlayerState))
			{
				CMPlayerState->LoadPlayerState(CurrentSaveGame);
				break;

			}
		}
		//UGameplayStatics::LoadGameFromSlot("PlayerSlot", 0);
		OnSaveGameLoaded.Broadcast(CurrentSaveGame);
	}
	else 
	{
		CurrentSaveGame = CastChecked<UCMPlayerSaveGame>(UGameplayStatics::CreateSaveGameObject(UCMPlayerSaveGame::StaticClass()));
	
		UE_LOG(LogTemp, Error, TEXT("Created New Save game data!"));
	}
	
}

void ACMGameModeBase::DeleteSaveGame()
{
	UGameplayStatics::DeleteGameInSlot("PlayerSlot", 0);
	CurrentSaveGame = CastChecked<UCMPlayerSaveGame>(UGameplayStatics::CreateSaveGameObject(UCMPlayerSaveGame::StaticClass()));
	UE_LOG(LogTemp, Warning, TEXT("Deleted Save Game Data!"));
}

void ACMGameModeBase::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	//ACMPlayerController* CMNewPlayer = Cast<ACMPlayerController>(NewPlayer);
	
	Super::HandleStartingNewPlayer_Implementation(NewPlayer);

	LoadSaveGame();
	UE_LOG(LogTemp, Warning, TEXT("CurrentSaveGame valid after load: %s"), IsValid(CurrentSaveGame) ? TEXT("true") : TEXT("false"));
}
//void ACMGameModeBase::HandleStartingNewPlayer_Implementation(APlayerController* Player)
//{
	//ACMPlayerState* PlayerState = Player->GetPlayerState<ACMPlayerState>();
	//if (IsValid(PlayerState))
	//{
		//PlayerState->LoadPlayerState(CurrentSaveGame);
	//}
//}
