// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class ASSIGNMENTPROJECTV2_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		class UCameraComponent* m_playerCamera;
	UPROPERTY(EditAnywhere)
		class USpringArmComponent* m_springArm;

	UPROPERTY()
		UArrowComponent* m_arrow;

	UPROPERTY(EditAnywhere)
		float actorSpeed;

	UFUNCTION()
		void MovePlayerForward(float val);
	UFUNCTION()
		void MovePlayerSide(float val);
	UFUNCTION()
		void RotatePlayerX(float val);
	UFUNCTION()
		void RotatePlayerY(float val);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	float deltaTime;
	float currentCamRotation = 0;
	float maxCamRotation = 85;
	float camOffset = 0;

};
