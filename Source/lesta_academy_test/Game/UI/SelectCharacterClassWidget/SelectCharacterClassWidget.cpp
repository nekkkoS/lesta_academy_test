// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectCharacterClassWidget.h"

#include "Components/Button.h"
#include "lesta_academy_test/Game/PlayerCharacter/PlayerCharacter.h"

void USelectCharacterClassWidget::NativeConstruct()
{
	Super::NativeConstruct();


	WarriorBtn->OnClicked.AddDynamic(this, &USelectCharacterClassWidget::OnWarriorBtnClicked);
	BarbarianBtn->OnClicked.AddDynamic(this, &USelectCharacterClassWidget::OnBarbarianBtnClicked);
	RogueBtn->OnClicked.AddDynamic(this, &USelectCharacterClassWidget::OnRogueBtnClicked);
}

void USelectCharacterClassWidget::NativeDestruct()
{
	WarriorBtn->OnClicked.RemoveDynamic(this, &USelectCharacterClassWidget::OnWarriorBtnClicked);
	BarbarianBtn->OnClicked.RemoveDynamic(this, &USelectCharacterClassWidget::OnBarbarianBtnClicked);
	RogueBtn->OnClicked.RemoveDynamic(this, &USelectCharacterClassWidget::OnRogueBtnClicked);
	
	
	Super::NativeDestruct();
}

void USelectCharacterClassWidget::OnRogueBtnClicked()
{
	OnClassSelected.Broadcast(ECharacterClass::Rogue);
	RemoveFromParent();
}

void USelectCharacterClassWidget::OnWarriorBtnClicked()
{
	OnClassSelected.Broadcast(ECharacterClass::Warrior);
	RemoveFromParent();
}

void USelectCharacterClassWidget::OnBarbarianBtnClicked()
{
	OnClassSelected.Broadcast(ECharacterClass::Barbarian);
	RemoveFromParent();
}
