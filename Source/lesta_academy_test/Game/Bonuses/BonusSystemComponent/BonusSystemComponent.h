// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BonusSystemComponent.generated.h"


struct FFightInfo;
class AEnemyCharacter;
class APlayerCharacter;
class UBonusBase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LESTA_ACADEMY_TEST_API UBonusSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBonusSystemComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	
	void AddBonus(const TSubclassOf<UBonusBase> BonusClass);

	void RemoveAllBonuses();
	
	void ApplyBonuses(FFightInfo& FightInfo) const;

protected:
	
	UPROPERTY(EditDefaultsOnly, Instanced, BlueprintReadWrite, Category="Bonuses")
	TArray<UBonusBase*> ActiveBonuses;
};
