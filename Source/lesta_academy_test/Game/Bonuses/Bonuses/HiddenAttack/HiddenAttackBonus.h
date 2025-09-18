// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "lesta_academy_test/Game/Bonuses/BonusBase/BonusBase.h"
#include "HiddenAttackBonus.generated.h"

/**
 * 
 */
UCLASS()
class LESTA_ACADEMY_TEST_API UHiddenAttackBonus : public UBonusBase
{
	GENERATED_BODY()

public:

	virtual void Apply() override;
};
