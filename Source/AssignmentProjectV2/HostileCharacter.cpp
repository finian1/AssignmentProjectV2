// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/ArrowComponent.h"
#include "HostileCharacter.h"

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



}

// Called to bind functionality to input
void AHostileCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

