// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

class UHUDWidget;
/**
 * 
 */
UCLASS()
class LESTA_ACADEMY_TEST_API AMyHUD : public AHUD
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

	UHUDWidget* GetHUDWidget() const {return HUDWidget;}

private:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UHUDWidget> HUDWidgetClass;

	UPROPERTY()
	UHUDWidget* HUDWidget;
};
