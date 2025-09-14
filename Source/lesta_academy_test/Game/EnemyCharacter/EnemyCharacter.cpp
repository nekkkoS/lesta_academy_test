// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"


// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyCharacter::InitializeRandomAttributes()
{
	Strength = FMath::RandRange(1, 3);
	Agility = FMath::RandRange(1, 3);
	Endurance = FMath::RandRange(1, 3);

	UE_LOG(LogTemp, Warning, TEXT("EnemyCharacter attributes initialized:"));
	UE_LOG(LogTemp, Warning, TEXT("Strength: %d"), Strength);
	UE_LOG(LogTemp, Warning, TEXT("Agility: %d"), Agility);
	UE_LOG(LogTemp, Warning, TEXT("Endurance: %d"), Endurance);
}

