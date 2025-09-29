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
	Barbarian,
	None
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
struct FClassParamsRow : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECharacterClass Class = ECharacterClass::None;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 HPPerLevel = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWeapon* DefaultWeapon = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UBonusBase> BonusAtLevel1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UBonusBase> BonusAtLevel2;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UBonusBase> BonusAtLevel3;
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


	// ------ Инициализация атрибутов ------

public:

	void InitializeRandomAttributes();

	
	// ------ Здоровье ------

public:
	
	void SetHP(const int32 NewHP) {HP = FMath::Clamp(NewHP, 0, MaxHP);}

	void ModifyHP(const int32 Delta) {SetHP(HP + Delta);}

	int32 GetHP() const {return HP;}

	void SetMaxHP(const int32 NewMaxHP) {MaxHP = FMath::Max(0, NewMaxHP);}

	void ModifyMaxHP(const int32 Delta) {SetMaxHP(MaxHP + Delta);}

	int32 GetMaxHP() const {return MaxHP;}

protected:

	UPROPERTY()
	int32 HP = 0;

	UPROPERTY()
	int32 MaxHP = 0;

	
	// ------ Базовые статы ------

public:

	int32 GetStrength() const {return Strength;}

	int32 GetAgility() const {return Agility;}

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

	
	// ------ Level up ------

public:

	void UpdateLevel(const ECharacterClass ClassForUpLevel);

	int32 GetTotalLevel() const {return TotalPlayerCharacterLevel;}

private:
	
	int32 TotalPlayerCharacterLevel = 0;


	// ------ Бонусы ------

public:

	UPROPERTY()
	UBonusSystemComponent* BonusSystem;

protected:

	UPROPERTY()
	FClassLevels ClassLevels;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="MyParams")
	UDataTable* ClassParamsTable;

	
	// ------ Бой ------

public:

	int32 TurnNumberInFight = 0;
};
