// Fill out your copyright notice in the Description page of Project Settings.


#include "BonusSystemComponent.h"

#include "lesta_academy_test/Game/Bonuses/Bonuses/HiddenAttack/HiddenAttackBonus.h"


// Sets default values for this component's properties
UBonusSystemComponent::UBonusSystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UBonusSystemComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UBonusSystemComponent::AddBonus(const TSubclassOf<UBonusBase> BonusClass)
{
	if (!BonusClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to create bonus: BonusClass is null"));
		return;
	}
	
	UBonusBase* Bonus = NewObject<UBonusBase>(this, BonusClass);
	if (!Bonus)
	{
		UE_LOG(LogTemp, Warning, TEXT("Create bonus failed for class: %s"), *BonusClass->GetName());
		return;
	}
	
	ActiveBonuses.Add(Bonus);
}

void UBonusSystemComponent::ApplyBonuses(APlayerCharacter* Player, AEnemyCharacter* Enemy, bool IsPlayerTurn) const
{
	for (const auto& Bonus : ActiveBonuses)
		Bonus->Apply();
}

