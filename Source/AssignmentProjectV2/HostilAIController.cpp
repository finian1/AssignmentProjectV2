// Fill out your copyright notice in the Description page of Project Settings.

#include "HostilAIController.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/TargetPoint.h"
#include "NavPoint.h"


void AHostilAIController::BeginPlay() {
	Super::BeginPlay();

	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ANavPoint::StaticClass(), m_waypoints);
	RunBehaviorTree(m_hostileTree);
	//RandomPatrol();
	//MoveToActor(PlayerPawn);
}

void AHostilAIController::Tick(float deltaTime) {
	Super::Tick(deltaTime);
	
	//MoveToActor(PlayerPawn);
}


void AHostilAIController::LookAtPlayer() {

}


void AHostilAIController::RandomPatrol() {
	if (!m_patrolling) {
		currentTarget = ChooseWaypoint();
		SetFocus(currentTarget);
		MoveToLocation(currentTarget->GetActorLocation());
	}
}

void AHostilAIController::OnMoveCompleted(FAIRequestID requestID, const FPathFollowingResult& result) {
	Super::OnMoveCompleted(requestID, result);
	UE_LOG(LogTemp, Warning, TEXT("Finished Move"));
	m_patrolling = false;
	//RandomPatrol();
}

AActor* AHostilAIController::ChooseWaypoint() {
	int index = FMath::RandRange(0, m_waypoints.Num() - 1);
	UE_LOG(LogTemp, Warning, TEXT("Moving to %i"), index);
	return m_waypoints[index];
}

