// Fill out your copyright notice in the Description page of Project Settings.


#include "DragonFeature.h"

#include "lesta_academy_test/Core/MyGameMode/MyGameMode.h"

void UDragonFeature::Apply(FUnitStats& OwnerStats, FUnitStats& OpponentStats)
{
	if (OwnerStats.TurnNumber % 3 == 0)
	{
		OwnerStats.TotalDamage += 3;
		
		const FString Message = FString::Printf(TEXT("Бонус: Дыхание огнём применёно для %s"),
		*OwnerStats.OwnerStatsNameForMsg);
		if (GEngine)
		{
			const FColor MessageColor = OwnerStats.IsPlayer ? FColor::Green : FColor::Red;
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, MessageColor, Message);
		}
	}
}
