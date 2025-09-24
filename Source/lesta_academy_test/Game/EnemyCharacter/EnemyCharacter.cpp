// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"

#include "lesta_academy_test/Game/Bonuses/BonusesAndFeatures/DragonFeature/DragonFeature.h"
#include "lesta_academy_test/Game/Bonuses/BonusesAndFeatures/HiddenAttack/HiddenAttack.h"
#include "lesta_academy_test/Game/Bonuses/BonusesAndFeatures/SkeletonFeature/SkeletonFeature.h"
#include "lesta_academy_test/Game/Bonuses/BonusesAndFeatures/SlimeFeature/SlimeFeature.h"
#include "lesta_academy_test/Game/Bonuses/BonusesAndFeatures/StoneSkin/StoneSkin.h"
#include "lesta_academy_test/Game/Bonuses/BonusSystemComponent/BonusSystemComponent.h"


// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BonusSystem = CreateDefaultSubobject<UBonusSystemComponent>(TEXT("BonusSystem"));
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	AddFeature();
}

void AEnemyCharacter::AddFeature() const
{
	if (!BonusSystem || !BonusClass)
	{
		UE_LOG(LogTemp, Error, TEXT("BonusSystem or BonusClass is not set."));
		return;
	}
	
	BonusSystem->AddBonus(BonusClass);
}

