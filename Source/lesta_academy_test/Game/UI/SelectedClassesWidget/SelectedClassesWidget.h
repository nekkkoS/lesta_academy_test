// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SelectedClassesWidget.generated.h"

struct FClassLevels;
class UTextBlock;
/**
 * 
 */
UCLASS()
class LESTA_ACADEMY_TEST_API USelectedClassesWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void UpdateBaseStats(int32 InStrength, int32 InAgility, int32 InEndurance) const;

	void UpdateCurrentWeapon(const FString& WeaponName) const;

	void UpdateClassLevels(const FClassLevels& Levels) const;

private:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* BaseStrengthNum;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* BaseAgilityNum;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* BaseEnduranceNum;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CurrentWeapon;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* RogueNum;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* WarriorNum;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* BarbarianNum;
};
