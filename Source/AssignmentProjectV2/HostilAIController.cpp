// Fill out your copyright notice in the Description page of Project Settings.

#include "HostilAIController.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/TargetPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavPoint.h"
#include "HostileCharacter.h"


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
	if (LineOfSightTo(PlayerPawn)) {
		GetBlackboardComponent()->SetValueAsBool(TEXT("HasLineOfSight"), true);
		SetFocus(PlayerPawn);
		AHostileCharacter* tempPawn = GetPawn<AHostileCharacter>();
		if (tempPawn) {
			tempPawn->FireWeapon();
		}
	}
	else {
		GetBlackboardComponent()->SetValueAsBool(TEXT("HasLineOfSight"), false);
		//EAIFocusPriority::Type type;
		ClearFocus(2U);
	}
	if (GetBlackboardComponent()->GetValueAsBool(TEXT("HasLineOfSight"))) {
		UE_LOG(LogTemp, Warning, TEXT("Can See Player"));
	}

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

