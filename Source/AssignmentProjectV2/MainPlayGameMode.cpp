// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayGameMode.h"
#include "SpawnPoint.h"
#include "HostilAIController.h"
#include "Kismet/GameplayStatics.h"

void AMainPlayGameMode::BeginPlay() {
	Super::BeginPlay();
	m_currentPlayerHealth = m_initialPlayerHealth;
	m_playerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnPoint::StaticClass(), m_enemySpawnNodes);
	SpawnHostiles();
	GetWorld()->GetTimerManager().SetTimer(m_waveSpawnTimer, this, &AMainPlayGameMode::SpawnHostiles, m_timeBetweenWaves, true);
	//EndGame();
}

void AMainPlayGameMode::Tick(float DeltaTime)
{
}

void AMainPlayGameMode::SpawnHostiles() {
	
	UE_LOG(LogTemp, Warning, TEXT("Number of spawn points is %i"), m_enemySpawnNodes.Num());
	for (int i = 0; i < m_enemySpawnNodes.Num(); i++) {
		if (m_enemySpawnNodes[i]->GetDistanceTo(m_playerPawn) > m_distToPreventSpawn) {
			if (FMath::RandRange(0, 100) < m_chanceForSpawn) {
				AHostileCharacter* tempChar = GetWorld()->SpawnActor<AHostileCharacter>(m_hostileCharacterPrefab, m_enemySpawnNodes[i]->GetActorLocation() + m_enemySpawnOffset, m_enemySpawnNodes[i]->GetActorRotation());
				//tempChar->GetController<AHostilAIController>()->RandomPatrol();
			}
		}
	}
}

void AMainPlayGameMode::EndGame() {
	UGameplayStatics::OpenLevel(this, FName(*m_mainMenuName), true);
}
