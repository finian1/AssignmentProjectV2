// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "HostilAIController.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGNMENTPROJECTV2_API AHostilAIController : public AAIController
{
	GENERATED_BODY()
protected:

	UPROPERTY()
		TArray<AActor*> m_waypoints;
	UPROPERTY()
		AActor* currentTarget;
	UFUNCTION()
		AActor* ChooseWaypoint();
	

	void OnMoveCompleted(FAIRequestID requestID, const FPathFollowingResult& result) override;

	class AActor* PlayerPawn;
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
public:
	UFUNCTION()
		void RandomPatrol();
private:
	bool m_patrolling = false;
};
