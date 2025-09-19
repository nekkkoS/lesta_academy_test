// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyCharacter.generated.h"

class UBonusSystemComponent;
class UWeapon;

UENUM(BlueprintType)
enum class EEnemyType : uint8
{
	Goblin,
	Skeleton,
	Slime,
	Ghost,
	Golem,
	Dragon
};

UCLASS()
class LESTA_ACADEMY_TEST_API AEnemyCharacter : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	// ------ Здоровье ------

public:
	
	void SetHP(const int32 NewHP) {HP = FMath::Max(0, NewHP);}

	void ModifyHP(const int32 Delta) {HP = FMath::Max(0, HP + Delta);}

	int32 GetHP() const {return HP;}

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "0"), Category="BaseStat")
	int32 HP = 0;

	
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "0"), Category="BaseStat")
	int32 WeaponDamage = 0;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "0"), Category="BaseStat")
	int32 Strength = 0;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "0"), Category="BaseStat")
	int32 Agility = 0;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "0"), Category="BaseStat")
	int32 Endurance = 0;

	
	// ------ Особенности ------

protected:

	void AddFeature() const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Feature")
	EEnemyType EnemyType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Feature")
	UBonusSystemComponent* FeatureSystem;

	// ------ ___ ------

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	UWeapon* RewardWeapon;

	void InitializeRandomAttributes();
};
