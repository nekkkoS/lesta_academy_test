// Fill out your copyright notice in the Description page of Project Settings.


#include "PoisonBonus.h"

#include "lesta_academy_test/Core/MyGameMode/MyGameMode.h"

void UPoisonBonus::Apply(FFightInfo& FightInfo)
{
	if (FightInfo.TurnNumber < 2)
		return;

	FightInfo.Damage += FightInfo.TurnNumber - 1;
}
