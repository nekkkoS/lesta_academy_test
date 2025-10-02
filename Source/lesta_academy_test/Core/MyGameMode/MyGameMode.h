// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MyGameMode.generated.h"

enum class ECharacterClass : uint8;
class UWeapon;
class UEndOfGameWidget;
class UPlayerWonFightWidget;
class UPlayerLostFightWidget;
enum class EWeaponDamageType : uint8;
class AEnemyCharacter;
class USelectCharacterClassWidget;
class APlayerCharacter;

USTRUCT(BlueprintType)
struct FUnitStats
{
	GENERATED_BODY()

	bool IsPlayer = true;
	FString OwnerStatsNameForMsg = TEXT("None");
	int32 Strength = 0;
	int32 Agility = 0;
	int32 Endurance = 0;
	int32 WeaponDamage = 0;
	EWeaponDamageType WeaponDamageType;
	int32 TurnNumber = 0;  // Номер удара юнита в бою
	int32 TotalDamage = 0;
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

private:

	void StartNewGame();

	bool CreatePlayerCharacter();

	bool SpawnRandomEnemy();

	void ShowSelectCharacterClassWidget() const;

	UFUNCTION()
	void HandleClassSelected(ECharacterClass CharacterClass);

	UPROPERTY()
	APlayerCharacter* Player;

	UPROPERTY()
	AEnemyCharacter* Enemy;

	UPROPERTY()
	TSubclassOf<USelectCharacterClassWidget> SelectCharacterWidgetClass;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MyParams")
	TSubclassOf<APlayerCharacter> PlayerBlueprintClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MyParams")
	TArray<TSubclassOf<AEnemyCharacter>> EnemyClassesSample;

	
	// ------ Бой ------

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MyParams")
	float DelayBetweenMoves = 0.5f;

private:

	void StartFight();

	void DoTurn();

	// Возвращает урон, который должен быть нанесён цели
	static int32 CalculateFight(APlayerCharacter* InPlayer, AEnemyCharacter* InEnemy,
		const bool IsPlayerTurn);

	FTimerHandle FightTurnTimer;

	bool IsPlayerTurn = false;

	int32 ConsecutiveWins = 0;


	// ------ После боя ------

private:

	void ShowPlayerLostFightWidget() const;

	UPROPERTY()
	TSubclassOf<UPlayerLostFightWidget> PlayerLostFightWidgetClass;

	void OnPlayerWonFight();

	void ShowPlayerWonFightWidget() const;

	UPROPERTY()
	TSubclassOf<UPlayerWonFightWidget> PlayerWonFightWidgetClass;

	void ShowEndOfGameWidget() const;

	UPROPERTY()
	TSubclassOf<UEndOfGameWidget> EndOfGameWidgetClass;

	UFUNCTION()
	void OnPlayerChangeWeapon();

	UFUNCTION()
	void ContinueGameAfterFight();

	bool DestroyEnemy();
};
