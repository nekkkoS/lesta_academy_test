// Fill out your copyright notice in the Description page of Project Settings.


#include "StrengthPlusOne.h"

#include "lesta_academy_test/Core/MyGameMode/MyGameMode.h"

void UStrengthPlusOne::Apply(FUnitStats& OwnerStats, FUnitStats& OpponentStats)
{
	OwnerStats.Strength += 1;
}
