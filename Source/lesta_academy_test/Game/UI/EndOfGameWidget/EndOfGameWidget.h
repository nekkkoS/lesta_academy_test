// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EndOfGameWidget.generated.h"

class UButton;
class UBackgroundBlur;
/**
 * 
 */
UCLASS()
class LESTA_ACADEMY_TEST_API UEndOfGameWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

private:

	UPROPERTY(meta = (BindWidget))
	UBackgroundBlur* BGBlur;

	UPROPERTY(meta = (BindWidget))
	UButton* RestartGameBtn;

	UFUNCTION()
	void OnRestartGameClicked();
};
