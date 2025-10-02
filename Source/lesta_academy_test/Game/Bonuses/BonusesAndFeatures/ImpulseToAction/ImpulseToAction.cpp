// Fill out your copyright notice in the Description page of Project Settings.


#include "ImpulseToAction.h"

#include "lesta_academy_test/Core/MyGameMode/MyGameMode.h"

void UImpulseToAction::Apply(FUnitStats& OwnerStats, FUnitStats& OpponentStats)
{
	if (OwnerStats.TurnNumber == 1)
	{
		OwnerStats.TotalDamage += OwnerStats.WeaponDamage;
		
		const FString Message = FString::Printf(TEXT("Порыв к действию применён для %s"),
		*OwnerStats.OwnerStatsNameForMsg);
		if (GEngine)
		{
			const FColor MessageColor = OwnerStats.IsPlayer ? FColor::Green : FColor::Red;
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, MessageColor, Message);
		}
	}
}
