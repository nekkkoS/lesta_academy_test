// Fill out your copyright notice in the Description page of Project Settings.


#include "AgilityPlusOne.h"

#include "lesta_academy_test/Core/MyGameMode/MyGameMode.h"

void UAgilityPlusOne::Apply(FFightInfo& FightInfo)
{
	FightInfo.AttackerAgility += 1;
}
