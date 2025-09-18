// Fill out your copyright notice in the Description page of Project Settings.


#include "HiddenAttackBonus.h"

#include "lesta_academy_test/Core/MyGameMode/MyGameMode.h"

void UHiddenAttackBonus::Apply(FFightInfo& FightInfo)
{
	if (FightInfo.AttackerAgility > FightInfo.DefenderAgility)
		FightInfo.Damage += 1;
}
