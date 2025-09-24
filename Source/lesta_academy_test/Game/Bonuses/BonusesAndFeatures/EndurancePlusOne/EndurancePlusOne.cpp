// Fill out your copyright notice in the Description page of Project Settings.


#include "EndurancePlusOne.h"

#include "lesta_academy_test/Core/MyGameMode/MyGameMode.h"

void UEndurancePlusOne::Apply(FUnitStats& OwnerStats, FUnitStats& OpponentStats)
{
	OwnerStats.Agility++;
}
