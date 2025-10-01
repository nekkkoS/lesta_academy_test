// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HPWidget.generated.h"

class APlayerCharacter;
class UTextBlock;
/**
 * 
 */
UCLASS()
class LESTA_ACADEMY_TEST_API UHPWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CurrentHP;
};
