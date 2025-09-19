// Fill out your copyright notice in the Description page of Project Settings.


#include "ImpulseToAction.h"

#include "lesta_academy_test/Core/MyGameMode/MyGameMode.h"

void UImpulseToAction::Apply(FFightInfo& FightInfo)
{
	if (FightInfo.TurnNumber == 1)
		FightInfo.AttackerWeaponDamage *= 2;
}
