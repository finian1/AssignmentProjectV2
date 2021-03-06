// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MainPlayGameMode.h"
#include "Math/UnrealMathUtility.h"
#include "Components/PrimitiveComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_arrow = FindComponentByClass<UArrowComponent>();

	m_springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	m_springArm->SetupAttachment(RootComponent);

	m_playerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	m_playerCamera->SetupAttachment(m_springArm);

	m_gunHoldPoint = CreateDefaultSubobject<USceneComponent>(TEXT("GunPoint"));
	m_gunHoldPoint->SetupAttachment(RootComponent);

	m_firearm = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Firearm"));
	m_firearm->SetupAttachment(m_gunHoldPoint);

	m_gunFirePoint = CreateDefaultSubobject<USceneComponent>(TEXT("FirePoint"));
	m_gunFirePoint->SetupAttachment(RootComponent);

	m_springArm->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f));
	m_springArm->SetRelativeRotation(FRotator(-30.0f, 0.0f, 0.0f));

	m_playerCamera->SetRelativeLocation(FVector(0.0f,0.0f,0.0f));
	m_playerCamera->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));

	m_springArm->bEnableCameraLag = true;
	m_springArm->bEnableCameraRotationLag = true;
	m_springArm->TargetArmLength = 300.0f;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	deltaTime = DeltaTime;
	TargetPosition();
}

void APlayerCharacter::TargetPosition() {
	if (targetPoint) {
		//UE_LOG(LogTemp, Warning, TEXT("Targeting..."));

		FVector start = m_gunFirePoint->GetComponentLocation();
		FVector forwardVector = m_gunFirePoint->GetForwardVector();
		FVector end = (forwardVector * targetDistance) + start;

		FHitResult hit;
		
		
		ECollisionChannel channel = ECC_WorldStatic;
		

		if (GetWorld()->LineTraceSingleByObjectType(hit, start, end, ECC_MAX, ignoreParams)) {
			//UE_LOG(LogTemp, Warning, TEXT("Target hit something"));
			targetPoint->SetActorLocation(hit.ImpactPoint);
		}
		else {
			//UE_LOG(LogTemp, Warning, TEXT("Target missed"));
			targetPoint->SetActorLocation(targetPointStore);
		}
		//DrawDebugLine(GetWorld(), start, hit.ImpactPoint, FColor::Green, false, 0, 0, 5);

		//targetPoint->SetActorLocation(m_gunFirePoint->GetForwardVector() * targetDistance);
	}
}

void APlayerCharacter::MovePlayerForward(float val) {
	//FVector movement = FVector(val * actorSpeed * deltaTime, 0.0f, 0.0f);
	this->AddMovementInput(this->GetActorForwardVector() * val * actorSpeed * deltaTime);
	//AddActorLocalOffset(movement);
}

void APlayerCharacter::MovePlayerSide(float val) {
	//FVector movement = FVector(0.0f, val * actorSpeed * deltaTime, 0.0f);
	this->AddMovementInput(this->GetActorRightVector() * val * actorSpeed * deltaTime);
	//AddActorLocalOffset(movement);
}

void APlayerCharacter::RotatePlayerX(float val) {
	//FRotator rotation = FRotator(0.0f, val, 0.0f);
	this->AddControllerYawInput(val);
	//AddActorLocalRotation(rotation);
}

void APlayerCharacter::OnFire() {
	if (m_projectileClass) {

		UGameplayStatics::PlaySoundAtLocation(
			GetWorld(),
			m_mySound,
			GetActorLocation(),
			1.0f,
			1.0f,
			0.0f
		);


		FVector spawnLocation = m_gunFirePoint->GetComponentLocation();
		FRotator spawnRotation = m_gunFirePoint->GetComponentRotation();
		/*AProjectile* tempProjectile = GetWorld()->SpawnActor<AProjectile>(m_projectileClass, spawnLocation, spawnRotation);
		ignoreParams.AddIgnoredActor(tempProjectile);
		if (tempProjectile) {
			tempProjectile->SetOwner(this);
		}*/

		FVector start = m_gunFirePoint->GetComponentLocation();
		FVector forwardVector = m_gunFirePoint->GetForwardVector();
		FVector end = (forwardVector * targetDistance) + start;

		FHitResult hit;

		if (GetWorld()->LineTraceSingleByObjectType(hit, start, end, ECC_MAX, ignoreParams)) {
			//UE_LOG(LogTemp, Warning, TEXT("Target hit something"));
			if (hit.GetActor()) {
				float force = 1000.0f;
				UPrimitiveComponent* rootComp = Cast<UPrimitiveComponent>(hit.GetActor()->GetRootComponent());
				rootComp->AddImpulse(forwardVector * force * rootComp->GetMass());
				UGameplayStatics::ApplyDamage(hit.GetActor(), 100.0f, Controller, this, UDamageType::StaticClass());
			}
			
			
		}

	}
}

float APlayerCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) {
	Cast<AMainPlayGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->m_currentPlayerHealth -= DamageAmount;
	if (Cast<AMainPlayGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->m_currentPlayerHealth <= 0) {
		UGameplayStatics::OpenLevel(GetWorld(), "EndGame");
	}
	return 0.0f;
}

void APlayerCharacter::OnStopFire() {

}

void APlayerCharacter::RotatePlayerY(float val) {
	currentCamRotation += val;
	currentCamRotation = FMath::Clamp(currentCamRotation, -maxCamRotation, maxCamRotation);
	FRotator rotation = FRotator(currentCamRotation, camOffset, 0.0f);
	m_springArm->SetRelativeRotation(rotation);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveSide", this, &APlayerCharacter::MovePlayerSide);
	PlayerInputComponent->BindAxis("MoveFront", this, &APlayerCharacter::MovePlayerForward);
	PlayerInputComponent->BindAxis("RotateX", this, &APlayerCharacter::RotatePlayerX);
	PlayerInputComponent->BindAxis("RotateY", this, &APlayerCharacter::RotatePlayerY);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerCharacter::OnFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &APlayerCharacter::OnStopFire);

}

