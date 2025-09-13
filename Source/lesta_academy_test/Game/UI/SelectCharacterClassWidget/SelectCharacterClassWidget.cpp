// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectCharacterClassWidget.h"

#include "Components/Button.h"

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

void USelectCharacterClassWidget::OnWarriorBtnClicked()
{
	OnClassSelected.Broadcast("Warrior");
	RemoveFromParent();
}

void USelectCharacterClassWidget::OnBarbarianBtnClicked()
{
	OnClassSelected.Broadcast("Barbarian");
	RemoveFromParent();
}

void USelectCharacterClassWidget::OnRogueBtnClicked()
{
	OnClassSelected.Broadcast("Rogue");
	RemoveFromParent();
}
