// Fill out your copyright notice in the Description page of Project Settings.


#include "SkeletonFeatureBonus.h"

#include "lesta_academy_test/Core/MyGameMode/MyGameMode.h"
#include "lesta_academy_test/Game/Weapon/Weapon.h"

void USkeletonFeatureBonus::Apply(FFightInfo& FightInfo)
{
	if (FightInfo.AttackerWeaponDamageType == EWeaponDamageType::Bludgeoning)
	{
		FightInfo.AttackerTotalDamage *= 2;
	}
}
