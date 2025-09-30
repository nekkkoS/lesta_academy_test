// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectedClassesWidget.h"

#include "Components/TextBlock.h"
#include "lesta_academy_test/Game/PlayerCharacter/PlayerCharacter.h"

void USelectedClassesWidget::UpdateClassLevels(const FClassLevels& Levels) const
{
	if (RogueNum)
	{
		RogueNum->SetText(FText::AsNumber(Levels.Rogue));
	}
	if (WarriorNum)
	{
		WarriorNum->SetText(FText::AsNumber(Levels.Warrior));
	}
	if (BarbarianNum)
	{
		BarbarianNum->SetText(FText::AsNumber(Levels.Barbarian));
	}
}
