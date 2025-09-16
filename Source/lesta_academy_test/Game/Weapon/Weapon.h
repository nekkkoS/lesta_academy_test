// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Weapon.generated.h"

UENUM(BlueprintType)
enum class EWeaponDamageType : uint8
{
	Slashing,     // Рубящий
	Bludgeoning,  // Дробящий
	Piercing      // Колющий
};

/**
 * 
 */
UCLASS()
class LESTA_ACADEMY_TEST_API UWeapon : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName WeaponName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 BaseDamage = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EWeaponDamageType DamageType = EWeaponDamageType::Slashing;
	
};
