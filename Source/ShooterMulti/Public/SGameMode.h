// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Components/SHealthComponent.h"
#include "SGameState.h"
#include "SPlayerState.h"
#include "SGameMode.generated.h"


enum class EWaveState : uint8;


//custom event for when a player is killed
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnActorKilled, AActor*, VictimActor, AActor*, KillerActor, AController*, KillerController);   //send killed actor, killer actor


/**
 * 
 */
UCLASS()
class SHOOTERMULTI_API ASGameMode : public AGameModeBase
{
	GENERATED_BODY()

	FTimerHandle TimerHandle_AISpawner;

protected:
	int32 NumOfBotsToSpawn;
	int32 WaveCount;
	FTimerHandle TimerHandle_NextWaveStart;

	UPROPERTY(EditDefaultsOnly, Category = "GameMode")
		float TimeBetweenWaves;


protected:

	//hook for BP to single Single AI
	UFUNCTION(BlueprintImplementableEvent, Category = "GameMode")
	void SpawnNewBot();

	void StartWave();

	void EndWave();

	void PrepareForNextWave();

	void SpawnBotTimerElapsed();

	void CheckWaveState();

	void CheckAnyPlayersAlive();

	void GameOver();

	void SetWaveState(EWaveState newState);

	void RestartDeadPlayers();

public:
	ASGameMode();

	virtual void StartPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(BlueprintAssignable, Category = "GameMode")
	FOnActorKilled OnActorKilled;

};
