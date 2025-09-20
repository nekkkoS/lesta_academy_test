// Fill out your copyright notice in the Description page of Project Settings.


#include "EndOfGameWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "lesta_academy_test/Core/MyGameMode/MyGameMode.h"

void UEndOfGameWidget::NativeConstruct()
{
	Super::NativeConstruct();

	RestartGameBtn->OnClicked.AddDynamic(this, &UEndOfGameWidget::OnRestartGameClicked);
}

void UEndOfGameWidget::NativeDestruct()
{
	RestartGameBtn->OnClicked.RemoveDynamic(this, &UEndOfGameWidget::OnRestartGameClicked);
	
	Super::NativeDestruct();
}

void UEndOfGameWidget::OnRestartGameClicked()
{
	if (UWorld* World = GetWorld())
	{
		if (AMyGameMode* GM = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(World)))
		{
			GM->RestartGame();
		}
	}
}
