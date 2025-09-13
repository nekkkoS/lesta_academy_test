// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MyGameMode.generated.h"

class USelectCharacterClassWidget;
class APlayerCharacter;
/**
 * 
 */
UCLASS()
class LESTA_ACADEMY_TEST_API AMyGameMode : public AGameMode
{
	GENERATED_BODY()

public:

	AMyGameMode();

	virtual void BeginPlay() override;

protected:

	UPROPERTY()
	APlayerCharacter* Player;

	void StartNewGame();
	
	void StartNextFight();
	
	void OnPlayerWonFight();
	
	void OnPlayerLostFight();

	int32 ConsecutiveWins = 0;

	UPROPERTY()
	TSubclassOf<USelectCharacterClassWidget> SelectCharacterWidgetClass;

	UFUNCTION()
	void HandleClassSelected(const FString& CharacterClass);
};
