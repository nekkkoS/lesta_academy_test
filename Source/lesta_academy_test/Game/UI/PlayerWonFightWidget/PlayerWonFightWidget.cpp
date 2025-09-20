// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerWonFightWidget.h"

#include "Components/Button.h"

void UPlayerWonFightWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ChangeWeaponBtn->OnClicked.AddDynamic(this, &UPlayerWonFightWidget::OnChangeWeaponBtnClicked);
	ContinueBtn->OnClicked.AddDynamic(this, &UPlayerWonFightWidget::OnChangeContinueBtnClicked);
}

void UPlayerWonFightWidget::NativeDestruct()
{
	ChangeWeaponBtn->OnClicked.RemoveDynamic(this, &UPlayerWonFightWidget::OnChangeWeaponBtnClicked);
	ContinueBtn->OnClicked.RemoveDynamic(this, &UPlayerWonFightWidget::OnChangeContinueBtnClicked);
	
	Super::NativeDestruct();
}

void UPlayerWonFightWidget::OnChangeWeaponBtnClicked()
{
	OnWeaponChange.Broadcast();
}

void UPlayerWonFightWidget::OnChangeContinueBtnClicked()
{
	OnContinueGame.Broadcast();
	RemoveFromParent();
}
