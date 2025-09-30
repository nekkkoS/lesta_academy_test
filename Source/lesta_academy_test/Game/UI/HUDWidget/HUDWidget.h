// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

class USelectedClassesWidget;
/**
 * 
 */
UCLASS()
class LESTA_ACADEMY_TEST_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget))
	USelectedClassesWidget* SelectedClassesWidget;
};
