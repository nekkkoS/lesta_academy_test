// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectedClassesWidget.h"

#include "Components/TextBlock.h"
#include "lesta_academy_test/Game/PlayerCharacter/PlayerCharacter.h"

void USelectedClassesWidget::UpdateBaseStats(int32 InStrength, int32 InAgility, int32 InEndurance) const
{
	BaseStrengthNum->SetText(FText::AsNumber(InStrength));
	BaseAgilityNum->SetText(FText::AsNumber(InAgility));
	BaseEnduranceNum->SetText(FText::AsNumber(InEndurance));
}

void USelectedClassesWidget::UpdateCurrentWeapon(const FString& WeaponName) const
{
	CurrentWeapon->SetText(FText::FromString(WeaponName));
}

void USelectedClassesWidget::UpdateClassLevels(const FClassLevels& Levels) const
{
	RogueNum->SetText(FText::AsNumber(Levels.Rogue));
	WarriorNum->SetText(FText::AsNumber(Levels.Warrior));
	BarbarianNum->SetText(FText::AsNumber(Levels.Barbarian));
}
