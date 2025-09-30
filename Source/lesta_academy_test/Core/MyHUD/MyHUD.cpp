// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"

#include "lesta_academy_test/Game/UI/HUDWidget/HUDWidget.h"

void AMyHUD::BeginPlay()
{
	Super::BeginPlay();

	if (!IsValid(HUDWidgetClass))
	{
		UE_LOG(LogTemp, Error, TEXT("HUDWidgetClass is not set"));
		return;
	}

	HUDWidget = CreateWidget<UHUDWidget>(GetWorld(), HUDWidgetClass);
	if (!HUDWidget)
	{
		UE_LOG(LogTemp, Error, TEXT("Error to create HUDWidget."));
		return;
	}

	HUDWidget->AddToViewport();
}
