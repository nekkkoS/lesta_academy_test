// Fill out your copyright notice in the Description page of Project Settings.


#include "Rage.h"

#include "lesta_academy_test/Core/MyGameMode/MyGameMode.h"

void URage::Apply(FUnitStats& OwnerStats, FUnitStats& OpponentStats)
{
	if (OwnerStats.TurnNumber < 4)
		OwnerStats.TotalDamage += 2;
	else
		OwnerStats.TotalDamage -= 1;
}
