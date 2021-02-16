// Fill out your copyright notice in the Description page of Project Settings.

#include "SGameMode.h"
#include "TimerManager.h"
#include "EngineUtils.h"

class USHealthComponent;
class APawn;
class ASGameState;
class APlayerState;

ASGameMode::ASGameMode()
{
	TimeBetweenWaves = 4.0f;

	GameStateClass = ASGameState::StaticClass();
	PlayerStateClass = ASPlayerState::StaticClass();


	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 1.0f;
}

void ASGameMode::CheckWaveState()
{
	bool bIsPreparingForWave = GetWorldTimerManager().IsTimerActive(TimerHandle_NextWaveStart);

	if (NumOfBotsToSpawn > 0 || bIsPreparingForWave)
		return;
	
	bool bIsAnyBotAlive = false;

	for (TActorIterator<APawn> It(GetWorld(),APawn::StaticClass()); It; ++It)
	{
		APawn* TestPawn = *It;
		if (TestPawn == NULL || TestPawn->IsPlayerControlled())
		{
			continue;
		}

		USHealthComponent* HealthComp = Cast<USHealthComponent>(TestPawn->GetComponentByClass(USHealthComponent::StaticClass()));
		if (HealthComp && HealthComp->GetHealth() > 0.0f)
		{

			bIsAnyBotAlive = true;
			break;

		}

	}
	
	if (!bIsAnyBotAlive)
	{

		SetWaveState(EWaveState::WaveComplete);

		PrepareForNextWave();
	}
	
}


void ASGameMode::StartPlay()
{
	Super::StartPlay();

	PrepareForNextWave();

}

void ASGameMode::CheckAnyPlayersAlive()
{

	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		APlayerController* PC = It->Get();
		if (PC && PC->GetPawn())
		{
			APawn* MyPawn = PC->GetPawn();
			USHealthComponent* HealthComp = Cast<USHealthComponent>(MyPawn->GetComponentByClass(USHealthComponent::StaticClass()) );
			if (ensure(HealthComp) && HealthComp->GetHealth() > 0.0f )
			{
				//UE_LOG(LogTemp, Log, TEXT("players still alive));

				return;
			}
		}
	}

	//no player alive
	GameOver();


}

void ASGameMode::GameOver()
{

	EndWave();

	//finish up match

	SetWaveState(EWaveState::GameOver);
}

void ASGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	CheckWaveState();
	CheckAnyPlayersAlive();
}

void ASGameMode::SetWaveState(EWaveState newState)
{

	ASGameState* GS = GetGameState<ASGameState>();
	if (ensureAlways(GS))
	{
		GS->SetWaveState(newState);
	}
}

void ASGameMode::RestartDeadPlayers()
{
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		APlayerController* PC = It->Get();
		if (PC && PC->GetPawn() == nullptr)
		{

			RestartPlayer(PC);

		}




	}

}


void ASGameMode::StartWave() {

	++WaveCount;
	NumOfBotsToSpawn = 2 * WaveCount;

	GetWorldTimerManager().SetTimer(TimerHandle_AISpawner,this, &ASGameMode::SpawnBotTimerElapsed, 1.0f,true,0.0f);


	SetWaveState(EWaveState::WaveInProgress);
}


void ASGameMode::EndWave() {


	GetWorldTimerManager().ClearTimer(TimerHandle_AISpawner);

	SetWaveState(EWaveState::WaitingToComplete);

}

void ASGameMode::PrepareForNextWave() {


	//set timer
	GetWorldTimerManager().SetTimer(TimerHandle_NextWaveStart, this, &ASGameMode::StartWave, TimeBetweenWaves, false);


	SetWaveState(EWaveState::WaitingToStart);

	RestartDeadPlayers();
	//StartWave();
}



void ASGameMode::SpawnBotTimerElapsed() {

	SpawnNewBot();

	--NumOfBotsToSpawn;

	if (NumOfBotsToSpawn <= 0)
		EndWave();

}

