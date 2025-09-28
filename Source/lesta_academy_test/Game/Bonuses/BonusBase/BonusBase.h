// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "BonusBase.generated.h"

struct FUnitStats;
/**
 * 
 */
UCLASS()
class LESTA_ACADEMY_TEST_API UBonusBase : public UObject
{
	GENERATED_BODY()

public:
	
	virtual void Apply(FUnitStats& OwnerStats, FUnitStats& OpponentStats) PURE_VIRTUAL(UBonusBase::Apply);
};
