// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MyGameMode.generated.h"

enum class EWeaponDamageType : uint8;
class AEnemyCharacter;
class USelectCharacterClassWidget;
class APlayerCharacter;

USTRUCT(BlueprintType)
struct FFightInfo
{
	GENERATED_BODY()
	
	int32 Damage = 0;
			
	int32 AttackerStrength = 0;
	int32 AttackerAgility = 0;
	int32 AttackerEndurance = 0;
	int32 AttackerWeaponDamage = 0;
	EWeaponDamageType AttackerWeaponDamageType;

	int32 DefenderStrength = 0;
	int32 DefenderAgility = 0;
	int32 DefenderEndurance = 0;
	int32 DefenderWeaponDamage = 0;

	int32 TurnNumber = 0;

	int32 AttackerTotalDamage = 0;
};

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

	UPROPERTY()
	AEnemyCharacter* Enemy;

	void StartNewGame();
	
	void StartNextFight();
	
	void OnPlayerWonFight();
	
	void OnPlayerLostFight();

	int32 ConsecutiveWins = 0;

	UPROPERTY()
	TSubclassOf<USelectCharacterClassWidget> SelectCharacterWidgetClass;

	UFUNCTION()
	void HandleClassSelected(const FString& CharacterClass);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Spawning")
	TSubclassOf<APlayerCharacter> PlayerBlueprintClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Spawning")
	TSubclassOf<AEnemyCharacter> EnemyBlueprintClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Spawning")
	TArray<TSubclassOf<AEnemyCharacter>> EnemyBlueprintClasses;

	void SpawnRandomEnemy(const FActorSpawnParameters& SpawnParams);

	void ShowSelectCharacterClassWidget() const;

	void SimulateFights();

	// Возвращает урон, который должен быть нанесён цели
	// TODO: Обратить внимание на то, как он будет применяться к здоровью цели (косяк с отрицательным значением)
	static int32 CalculateFight(const APlayerCharacter* InPlayer, const AEnemyCharacter* InEnemy, int32 TurnNumber,
		bool IsPlayerTurn);
};
