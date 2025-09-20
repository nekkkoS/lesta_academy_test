// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "lesta_academy_test/Game/Bonuses/BonusBase/BonusBase.h"
#include "EndurancePlusOne.generated.h"

/**
 * 
 */
UCLASS()
class LESTA_ACADEMY_TEST_API UEndurancePlusOne : public UBonusBase
{
	GENERATED_BODY()

public:

	virtual void Apply(FFightInfo& FightInfo) override;
};
