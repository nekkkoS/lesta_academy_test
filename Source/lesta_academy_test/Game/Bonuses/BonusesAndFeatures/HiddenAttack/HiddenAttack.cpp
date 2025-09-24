// Fill out your copyright notice in the Description page of Project Settings.


#include "HiddenAttack.h"

#include "lesta_academy_test/Core/MyGameMode/MyGameMode.h"

void UHiddenAttack::Apply(FUnitStats& OwnerStats, FUnitStats& OpponentStats)
{
	if (OwnerStats.Agility > OpponentStats.Agility)
		OwnerStats.TotalDamage += 1;
}
