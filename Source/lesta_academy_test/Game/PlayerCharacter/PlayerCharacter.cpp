// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "lesta_academy_test/Game/Bonuses/Bonuses/HiddenAttack/HiddenAttackBonus.h"
#include "lesta_academy_test/Game/Bonuses/BonusSystemComponent/BonusSystemComponent.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BonusSystem = CreateDefaultSubobject<UBonusSystemComponent>(TEXT("BonusSystem"));

	BonusTable = {
		{ECharacterClass::Rogue, 1, {UHiddenAttackBonus::StaticClass()}},
		/*{ECharacterClass::Rogue, 2, {UDexterityPlusOne::StaticClass()}},
		{ECharacterClass::Rogue, 3, {UPoisonBonus::StaticClass()}},

		{ECharacterClass::Warrior, 1, {UActionSurgeBonus::StaticClass()}},
		{ECharacterClass::Warrior, 2, {UShieldBonus::StaticClass()}},
		{ECharacterClass::Warrior, 3, {UStrengthPlusOne::StaticClass()}},

		{ECharacterClass::Barbarian, 1, {URageBonus::StaticClass()}},
		{ECharacterClass::Barbarian, 2, {UStoneSkinBonus::StaticClass()}},
		{ECharacterClass::Barbarian, 3, {UStaminaPlusOne::StaticClass()}}*/
	};
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerCharacter::UpdateBonuses()
{
	// if (ClassLevels.Rogue == 1)
	// 	BonusSystem->AddBonus(UHiddenAttackBonus::StaticClass());
	
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

