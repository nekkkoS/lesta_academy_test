// Fill out your copyright notice in the Description page of Project Settings.


#include "StoneSkin.h"

#include "lesta_academy_test/Core/MyGameMode/MyGameMode.h"

void UStoneSkin::Apply(FUnitStats& OwnerStats, FUnitStats& OpponentStats)
{
	OpponentStats.TotalDamage -= OwnerStats.Endurance;
}
