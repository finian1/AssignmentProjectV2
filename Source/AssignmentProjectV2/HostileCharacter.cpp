// Fill out your copyright notice in the Description page of Project Settings.

#include "HostileCharacter.h"
#include "Components/ArrowComponent.h"
#include "MainPlayGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/TargetPoint.h"


// Sets default values
AHostileCharacter::AHostileCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bCanEverTick = true;
	m_arrow = FindComponentByClass<UArrowComponent>();

	m_gunHoldPoint = CreateDefaultSubobject<USceneComponent>(TEXT("GunPoint"));
	m_gunHoldPoint->SetupAttachment(RootComponent);

	m_gunFirePoint = CreateDefaultSubobject<USceneComponent>(TEXT("FirePoint"));
	m_gunFirePoint->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AHostileCharacter::BeginPlay()
{
	Super::BeginPlay();
	

	
}

// Called every frame
void AHostileCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	deltaTime = DeltaTime;
	if (isFiring) {
		FireWeapon();
	}
	fireTimer -= deltaTime;


}

float AHostileCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser){
	m_health -= DamageAmount;
	if (m_health < 0.0f) {
		Cast<AMainPlayGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->AddScore(scoreOnDeath);
		Destroy();
	}
	return 0.0f;
}

void AHostileCharacter::FireWeapon() {
	if (fireTimer <= 0) {
		if (m_projectileClass) {
			FVector spawnLocation = m_gunFirePoint->GetComponentLocation();
			FRotator spawnRotation = m_gunFirePoint->GetComponentRotation();
			AProjectile* tempProjectile = GetWorld()->SpawnActor<AProjectile>(m_projectileClass, spawnLocation, spawnRotation);
			if (tempProjectile) {
				tempProjectile->SetOwner(this);
			}
		}
		fireTimer = 1 / fireRate;
	}
}


// Called to bind functionality to input
void AHostileCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

