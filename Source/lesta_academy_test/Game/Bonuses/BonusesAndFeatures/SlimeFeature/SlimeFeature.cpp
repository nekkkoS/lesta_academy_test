// Fill out your copyright notice in the Description page of Project Settings.


#include "SlimeFeature.h"

#include "lesta_academy_test/Core/MyGameMode/MyGameMode.h"
#include "lesta_academy_test/Game/Weapon/Weapon.h"

void USlimeFeature::Apply(FUnitStats& OwnerStats, FUnitStats& OpponentStats)
{
	if (OpponentStats.WeaponDamageType == EWeaponDamageType::Slashing)
		OpponentStats.TotalDamage -= OpponentStats.WeaponDamage;
}
