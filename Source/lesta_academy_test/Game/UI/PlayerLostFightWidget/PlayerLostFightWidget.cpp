// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerLostFightWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "lesta_academy_test/Core/MyGameMode/MyGameMode.h"

void UPlayerLostFightWidget::NativeConstruct()
{
	Super::NativeConstruct();

	RestartGameBtn->OnClicked.AddDynamic(this, &UPlayerLostFightWidget::OnRestartGameClicked);
}

void UPlayerLostFightWidget::NativeDestruct()
{
	RestartGameBtn->OnClicked.RemoveDynamic(this, &UPlayerLostFightWidget::OnRestartGameClicked);
	
	Super::NativeDestruct();
}

void UPlayerLostFightWidget::OnRestartGameClicked()
{
	if (UWorld* World = GetWorld())
	{
		if (AMyGameMode* GM = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(World)))
		{
			GM->RestartGame();
		}
	}
}
