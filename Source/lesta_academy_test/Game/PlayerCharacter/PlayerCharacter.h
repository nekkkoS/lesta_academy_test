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

	
	// ------ Здоровье ------

public:
	
	void SetHP(const int32 NewHP) {HP = FMath::Max(0, NewHP);}

	void ModifyHP(const int32 Delta) {HP = FMath::Max(0, HP + Delta);}

	int32 GetHP() const {return HP;}

	void SetMaxHP(const int32 NewMaxHP) {MaxHP = FMath::Max(0, NewMaxHP);}

	void ModifyMaxHP(const int32 Delta) {HP = FMath::Max(0, MaxHP + Delta);}

	int32 GetMaxHP() const {return MaxHP;}

	void ResetHP() {HP = MaxHP;}

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "0"), Category="BaseStat")
	int32 HP = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "0"), Category="BaseStat")
	int32 MaxHP = 0;
	
	// ------ Базовые статы ------
	// TODO: Ненужные сеттеры/геттеры можно будет убрать

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "0"), Category="BaseStat")
	int32 Strength = 0;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "0"), Category="BaseStat")
	int32 Agility = 0;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "0"), Category="BaseStat")
	int32 Endurance = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Name")
	FText UnitName;

	
	// ------ Бонусы ------

public:

	void UpdateBonuses();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Bonuses")
	UBonusSystemComponent* BonusSystem;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Bonuses")
	FClassLevels ClassLevels;

private:

	// static TArray<FClassBonusInfo> BonusTable;
	
	// ------ ___ ------

public:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	UWeapon* Weapon;

	void InitializeRandomAttributes();
};
