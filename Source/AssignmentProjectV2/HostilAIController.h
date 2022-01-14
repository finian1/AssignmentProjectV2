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
	virtual void BeginPlay() override;
};
