// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BonusSystemComponent.generated.h"


enum class EWeaponDamageType : uint8;
struct FUnitStats;
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
	
	void AddBonus(const TSubclassOf<UBonusBase>& BonusClass);

	void RemoveAllBonuses();
	
	void ApplyBonuses(FUnitStats& OwnerStats, FUnitStats& OpponentStats) const;

protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MyParams")
	TArray<UBonusBase*> ActiveBonuses;
};
