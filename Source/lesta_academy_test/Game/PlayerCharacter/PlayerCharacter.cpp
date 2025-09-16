// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerCharacter::InitializeRandomAttributes()
{
	Strength = FMath::RandRange(1, 3);
	Agility = FMath::RandRange(1, 3);
	Endurance = FMath::RandRange(1, 3);

	UE_LOG(LogTemp, Warning, TEXT("PlayerCharacter attributes initialized:"));
	UE_LOG(LogTemp, Warning, TEXT("Strength: %d"), Strength);
	UE_LOG(LogTemp, Warning, TEXT("Agility: %d"), Agility);
	UE_LOG(LogTemp, Warning, TEXT("Endurance: %d"), Endurance);
}

