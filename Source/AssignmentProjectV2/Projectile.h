// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile.generated.h"


UCLASS()
class ASSIGNMENTPROJECTV2_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* m_projectile;

	UPROPERTY(EditAnywhere)
		float movementSpeed = 1000.0f;

	UPROPERTY(EditAnywhere)
		class UProjectileMovementComponent* m_movement;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
