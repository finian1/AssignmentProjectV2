// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HostileCharacter.h"
#include "MainPlayGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGNMENTPROJECTV2_API AMainPlayGameMode : public AGameModeBase
{
	GENERATED_BODY()
protected:
	UPROPERTY()
		TArray<AActor*> m_enemySpawnNodes;
	UPROPERTY(EditAnywhere)
		TSubclassOf<AHostileCharacter> m_hostileCharacterPrefab;
	UPROPERTY(EditAnywhere)
		float m_distToPreventSpawn;
	UPROPERTY(EditAnywhere)
		float m_chanceForSpawn;
	UPROPERTY(EditAnywhere)
		FVector m_enemySpawnOffset;
	UPROPERTY(EditAnywhere)
		FString m_mainMenuName;
	UPROPERTY(EditAnywhere)
		float m_timeBetweenWaves;
	UPROPERTY()
		FTimerHandle m_waveSpawnTimer;
	UFUNCTION()
		void SpawnHostiles();


	class AActor* m_playerPawn;
public:
	UPROPERTY(EditAnywhere)
		float m_initialPlayerHealth;
	float m_currentPlayerHealth;
	UPROPERTY(EditAnywhere)
		int m_playerScore;

	UFUNCTION(BlueprintCallable, Category = "Main Play Functions")
		void EndGame();

private:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;

	
};
