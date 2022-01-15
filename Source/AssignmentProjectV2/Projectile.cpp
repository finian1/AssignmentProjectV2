// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "HostileCharacter.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_projectile = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	m_projectile->SetupAttachment(RootComponent);
	m_projectile->SetSimulatePhysics(true);
	m_projectile->SetNotifyRigidBodyCollision(true);

	m_movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	m_movement->MaxSpeed = movementSpeed;
	m_movement->InitialSpeed = movementSpeed;
	InitialLifeSpan = 10.0f;
	

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	OnActorHit.AddDynamic(this, &AProjectile::OnHit);

	
}

void AProjectile::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit) {

	UE_LOG(LogTemp, Warning, TEXT("Hit something!"));
	AActor* projectileOwner = GetOwner();
	if (projectileOwner && OtherActor) {
		if (projectileOwner->GetClass()->IsChildOf(AHostileCharacter::StaticClass())) {
			if (OtherActor->GetClass()->IsChildOf(APlayerCharacter::StaticClass())) {
				UGameplayStatics::ApplyDamage(OtherActor, projectileDamage, projectileOwner->GetInstigatorController(), this, UDamageType::StaticClass());
				
			}
		}
		else if (projectileOwner->GetClass()->IsChildOf(APlayerCharacter::StaticClass())) {
			if (OtherActor->GetClass()->IsChildOf(AHostileCharacter::StaticClass())) {


				UGameplayStatics::ApplyDamage(OtherActor, projectileDamage, projectileOwner->GetInstigatorController(), this, UDamageType::StaticClass());

				
			}
		}
	}
	Destroy();
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

