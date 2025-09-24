// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerCharacter.generated.h"

class UBonusBase;
class UBonusSystemComponent;
class UWeapon;

UENUM(BlueprintType)
enum class ECharacterClass : uint8
{
	Rogue,
	Warrior,
	Barbarian
};

USTRUCT(BlueprintType)
struct FClassBonusInfo
{
	GENERATED_BODY()
	
	ECharacterClass Class;
	int32 Level;
	TArray<TSubclassOf<UBonusBase>> Bonuses;
};

USTRUCT(BlueprintType)
struct FClassLevels
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Rogue = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Warrior = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Barbarian = 0;
};

USTRUCT(BlueprintType)
struct FClassBonusRow : public FTableRowBase
{
	GENERATED_BODY()

	// Класс персонажа (Разбойник / Воин / Варвар)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECharacterClass Class;

	// Уровень, на котором даётся бонус
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Level;

	// Бонусы
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<UBonusBase>> Bonuses;
};

UCLASS()
class LESTA_ACADEMY_TEST_API APlayerCharacter : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	// ------ Инициализация ------

public:

	void InitializeRandomAttributes();
	
	// ------ Здоровье ------

public:
	
	void SetHP(const int32 NewHP) {HP = FMath::Clamp(NewHP, 0, MaxHP);}

	void ModifyHP(const int32 Delta) {SetHP(HP + Delta);}

	int32 GetHP() const {return HP;}

	void SetMaxHP(const int32 NewMaxHP) {MaxHP = FMath::Max(1, NewMaxHP);}

	void ModifyMaxHP(const int32 Delta) {SetMaxHP(MaxHP + Delta);}

	int32 GetMaxHP() const {return MaxHP;}

	void ResetHP() {HP = MaxHP;}

protected:

	UPROPERTY()
	int32 HP = 0;

	UPROPERTY()
	int32 MaxHP = 0;

	
	// ------ Базовые статы ------

public:

	void SetStrength(const int32 NewStrength) {Strength = FMath::Max(0, NewStrength);}

	void ModifyStrength(const int32 Delta) {Strength = FMath::Max(0, Strength + Delta);}

	int32 GetStrength() const {return Strength;}

	void SetAgility(const int32 NewAgility) {Agility = FMath::Max(0, NewAgility);}

	void ModifyAgility(const int32 Delta) {Agility = FMath::Max(0, Agility + Delta);}

	int32 GetAgility() const {return Agility;}

	void SetEndurance(const int32 NewEndurance) {Endurance = FMath::Max(0, NewEndurance);}

	void ModifyEndurance(const int32 Delta) {Endurance = FMath::Max(0, Endurance + Delta);}

	int32 GetEndurance() const {return Endurance;}

protected:

	UPROPERTY()
	int32 Strength = 0;
	
	UPROPERTY()
	int32 Agility = 0;
	
	UPROPERTY()
	int32 Endurance = 0;


	// ------ Оружие ------

public:

	UPROPERTY()
	UWeapon* Weapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="MyParams")
	UWeapon* DefaultRogueWeapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="MyParams")
	UWeapon* DefaultWarriorWeapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="MyParams")
	UWeapon* DefaultBarbarianWeapon;

	
	// ------ Character Level ------

public:

	void IncreaseLevel();

	int32 GetCurrentLevel() const {return PlayerCharacterLevel;}

private:
	
	int32 PlayerCharacterLevel = 0;


	// ------ Бонусы ------

public:

	void AddBonuses() const;

	UPROPERTY()
	UBonusSystemComponent* BonusSystem;

	UPROPERTY()
	FClassLevels ClassLevels;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="MyParams")
	UDataTable* BonusDataTable;

private:

	void AddBonusesForClass(ECharacterClass Class, int32 Level, const TArray<FClassBonusRow*>& AllRows) const;

	
	// ------ Бой ------

public:

	int32 HitNumberInFight = 0;
};
