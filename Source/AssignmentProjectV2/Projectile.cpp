// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_projectile = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	m_projectile->SetupAttachment(RootComponent);
	m_projectile->SetSimulatePhysics(true);
	m_movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	m_movement->MaxSpeed = movementSpeed;
	m_movement->InitialSpeed = movementSpeed;
	InitialLifeSpan = 10.0f;
	

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

