// Fill out your copyright notice in the Description page of Project Settings.


#include "StoneSkin.h"

#include "lesta_academy_test/Core/MyGameMode/MyGameMode.h"

void UStoneSkin::Apply(FUnitStats& OwnerStats, FUnitStats& OpponentStats)
{
	OpponentStats.TotalDamage -= OwnerStats.Endurance;

	const FString Message = FString::Printf(TEXT("Каменная кожа применена для %s"),
		*OwnerStats.OwnerStatsNameForMsg);
	if (GEngine)
	{
		const FColor MessageColor = OwnerStats.IsPlayer ? FColor::Green : FColor::Red;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, MessageColor, Message);
	}
}
