// Fill out your copyright notice in the Description page of Project Settings.


#include "EndurancePlusOne.h"

#include "lesta_academy_test/Core/MyGameMode/MyGameMode.h"

void UEndurancePlusOne::Apply(FUnitStats& OwnerStats, FUnitStats& OpponentStats)
{
	OwnerStats.Agility++;

	const FString Message = FString::Printf(TEXT("Выносливость + 1 применена для %s"),
		*OwnerStats.OwnerStatsNameForMsg);
	if (GEngine)
	{
		const FColor MessageColor = OwnerStats.IsPlayer ? FColor::Green : FColor::Red;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, MessageColor, Message);
	}
}
