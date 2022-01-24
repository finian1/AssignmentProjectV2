// Fill out your copyright notice in the Description page of Project Settings.


#include "AimPoint.h"

// Sets default values
AAimPoint::AAimPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAimPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAimPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

