// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "PlayerCharacter.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Door Trigger"));
	trigger->SetupAttachment(RootComponent);
	doorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Mesh"));
	doorMesh->SetupAttachment(trigger);
	doorMesh->SetRelativeLocation(FVector(0, 0, 0));
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	trigger->OnComponentBeginOverlap.AddDynamic(this, &ADoor::OnOverlapBegin);
	trigger->OnComponentEndOverlap.AddDynamic(this, &ADoor::OnOverlapEnd);
}

void ADoor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Entered Door"));
	//FVector hidePos = FVector(GetActorLocation() + FVector(0, hideDistance, 0));
	if (OtherActor->GetClass()->IsChildOf(APlayerCharacter::StaticClass())) {
		doorMesh->SetRelativeLocation(FVector(0, 0, hideDistance));
	}
	
}
void ADoor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("Left Door"));
	if (OtherActor->GetClass()->IsChildOf(APlayerCharacter::StaticClass())) {
		doorMesh->SetRelativeLocation(FVector(0, 0, 0));
	}
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

