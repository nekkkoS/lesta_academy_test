// Fill out your copyright notice in the Description page of Project Settings.


#include "Shield.h"

#include "lesta_academy_test/Core/MyGameMode/MyGameMode.h"

void UShield::Apply(FFightInfo& FightInfo)
{
	if (FightInfo.DefenderStrength > FightInfo.AttackerStrength)
		FightInfo.Damage -= 3;
}
