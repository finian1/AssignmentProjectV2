// Fill out your copyright notice in the Description page of Project Settings.

#include "HostilAIController.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/TargetPoint.h"
#include "NavPoint.h"


void AHostilAIController::BeginPlay() {
	Super::BeginPlay();

	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ANavPoint::StaticClass(), m_waypoints);
	//MoveToActor(PlayerPawn);
}

void AHostilAIController::Tick(float deltaTime) {
	Super::Tick(deltaTime);
	
	//MoveToActor(PlayerPawn);
}


