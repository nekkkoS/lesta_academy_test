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

	// ------ Начало игры ------

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

	int32 ConsecutiveWins = 0;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MyParams")
	TSubclassOf<APlayerCharacter> PlayerBlueprintClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MyParams")
	TSubclassOf<AEnemyCharacter> EnemyBlueprintClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MyParams")
	TArray<TSubclassOf<AEnemyCharacter>> EnemyClassesSample;

	
	// ------ Бой ------

private:

	void StartFight();

	void DoTurn();

	// Возвращает урон, который должен быть нанесён цели
	// TODO: Обратить внимание на то, как он будет применяться к здоровью цели (косяк с отрицательным значением)
	static int32 CalculateFight(const APlayerCharacter* InPlayer, const AEnemyCharacter* InEnemy,
		const bool IsPlayerTurn);

	FTimerHandle FightTurnTimer;

	bool bPlayerTurn;

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
};
