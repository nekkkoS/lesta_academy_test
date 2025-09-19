// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"

#include "lesta_academy_test/Game/Bonuses/Bonuses/DragonFeature/DragonFeature.h"
#include "lesta_academy_test/Game/Bonuses/Bonuses/HiddenAttack/HiddenAttackBonus.h"
#include "lesta_academy_test/Game/Bonuses/Bonuses/SkeletonFeature/SkeletonFeatureBonus.h"
#include "lesta_academy_test/Game/Bonuses/Bonuses/SlimeFeature/SlimeFeature.h"
#include "lesta_academy_test/Game/Bonuses/Bonuses/StoneSkin/StoneSkin.h"
#include "lesta_academy_test/Game/Bonuses/BonusSystemComponent/BonusSystemComponent.h"


// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	FeatureSystem = CreateDefaultSubobject<UBonusSystemComponent>(TEXT("FeatureSystem"));
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	AddFeature();
}

void AEnemyCharacter::AddFeature() const
{
	if (!FeatureSystem)
		return;
	
	switch (EnemyType)
	{
	case EEnemyType::Goblin:
		break;
		
	case EEnemyType::Skeleton:
		FeatureSystem->AddBonus(USkeletonFeatureBonus::StaticClass());
		break;
		
	case EEnemyType::Slime:
		FeatureSystem->AddBonus(USlimeFeature::StaticClass());
		break;
		
	case EEnemyType::Ghost:
		FeatureSystem->AddBonus(UHiddenAttackBonus::StaticClass());
		break;
		
	case EEnemyType::Golem:
		FeatureSystem->AddBonus(UStoneSkin::StaticClass());
		break;

	case EEnemyType::Dragon:
		FeatureSystem->AddBonus(UDragonFeature::StaticClass());
		break;
		
	default:
		break;
	}
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

