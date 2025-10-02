// Fill out your copyright notice in the Description page of Project Settings.


#include "Rage.h"

#include "lesta_academy_test/Core/MyGameMode/MyGameMode.h"

void URage::Apply(FUnitStats& OwnerStats, FUnitStats& OpponentStats)
{
	if (OwnerStats.TurnNumber < 4)
		OwnerStats.TotalDamage += 2;
	else
		OwnerStats.TotalDamage -= 1;

	const FString Message = FString::Printf(TEXT("Ярость применена для %s"),
		*OwnerStats.OwnerStatsNameForMsg);
	if (GEngine)
	{
		const FColor MessageColor = OwnerStats.IsPlayer ? FColor::Green : FColor::Red;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, MessageColor, Message);
	}
}
