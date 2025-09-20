// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "lesta_academy_test/Game/Bonuses/BonusSystemComponent/BonusSystemComponent.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BonusSystem = CreateDefaultSubobject<UBonusSystemComponent>(TEXT("BonusSystem"));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerCharacter::IncreaseLevel()
{
	PlayerCharacterLevel++;
}

void APlayerCharacter::AddBonuses() const
{
	if (!BonusDataTable || !BonusSystem)
	{
		UE_LOG(LogTemp, Error, TEXT("BonusDataTable or BonusSystem is null"));
		return;
	}

	BonusSystem->RemoveAllBonuses();

	TArray<FClassBonusRow*> AllRows;
	BonusDataTable->GetAllRows(TEXT("Bonus Lookup"), AllRows);
	
	AddBonusesForClass(ECharacterClass::Rogue, ClassLevels.Rogue, AllRows);
	AddBonusesForClass(ECharacterClass::Warrior, ClassLevels.Warrior, AllRows);
	AddBonusesForClass(ECharacterClass::Barbarian, ClassLevels.Barbarian, AllRows);
}

void APlayerCharacter::AddBonusesForClass(ECharacterClass Class, int32 Level,
	const TArray<FClassBonusRow*>& AllRows) const
{
	for (int32 L = 1; L <= Level; ++L)
	{
		for (auto* Row : AllRows)
		{
			if (Row->Class == Class && Row->Level == L)
			{
				for (auto& BonusClass : Row->Bonuses)
				{
					BonusSystem->AddBonus(BonusClass);
				}
			}
		}
	}
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

