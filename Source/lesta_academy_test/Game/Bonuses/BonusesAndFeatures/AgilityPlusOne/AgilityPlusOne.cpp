// Fill out your copyright notice in the Description page of Project Settings.


#include "AgilityPlusOne.h"

#include "lesta_academy_test/Core/MyGameMode/MyGameMode.h"

void UAgilityPlusOne::Apply(FUnitStats& OwnerStats, FUnitStats& OpponentStats)
{
	OwnerStats.Agility++;
	
	const FString Message = FString::Printf(TEXT("Ловкость + 1 применена для %s"),
		*OwnerStats.OwnerStatsNameForMsg);
	if (GEngine)
	{
		const FColor MessageColor = OwnerStats.IsPlayer ? FColor::Green : FColor::Red;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, MessageColor, Message);
	}
}
