// Fill out your copyright notice in the Description page of Project Settings.


#include "Shield.h"

#include "lesta_academy_test/Core/MyGameMode/MyGameMode.h"

void UShield::Apply(FUnitStats& OwnerStats, FUnitStats& OpponentStats)
{
	if (OwnerStats.Strength > OpponentStats.Strength)
		OpponentStats.TotalDamage -= 3;
}
