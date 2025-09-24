// Fill out your copyright notice in the Description page of Project Settings.


#include "Poison.h"

#include "lesta_academy_test/Core/MyGameMode/MyGameMode.h"

void UPoison::Apply(FUnitStats& OwnerStats, FUnitStats& OpponentStats)
{
	if (OwnerStats.TurnNumber < 2)
		return;

	OwnerStats.TotalDamage += OwnerStats.TurnNumber - 1;
}
