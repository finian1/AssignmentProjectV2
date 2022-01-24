// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Projectile.h"
#include "HostileCharacter.generated.h"

UCLASS()
class ASSIGNMENTPROJECTV2_API AHostileCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHostileCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
		class USceneComponent* m_gunHoldPoint;
	UPROPERTY(EditAnywhere)
		class USceneComponent* m_gunFirePoint;
	UPROPERTY(EditAnywhere)
		TSubclassOf<AProjectile> m_projectileClass;

	UPROPERTY()
		UArrowComponent* m_arrow;

	

	UPROPERTY(EditAnywhere)
		float actorSpeed;
	UFUNCTION()
		virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
			AController* EventInstigator, AActor* DamageCauser) override;
	

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable,Category="TestCategory")
		void FireWeapon();
private:
	float deltaTime;
	UPROPERTY(EditAnywhere)
		float fireRate = 2;


	float m_health = 10.0f;
	int scoreOnDeath = 10;
	float fireTimer = 0;
	bool isFiring = true;
};
