// Fill out your copyright notice in the Description page of Project Settings.


#include "AgilityPlusOneBonus.h"

#include "lesta_academy_test/Core/MyGameMode/MyGameMode.h"

void UAgilityPlusOneBonus::Apply(FFightInfo& FightInfo)
{
	FightInfo.AttackerAgility += 1;
}
