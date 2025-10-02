// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyCharacter.generated.h"

class UNiagaraSystem;
class UHPWidget;
class UWidgetComponent;
class UBonusBase;
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
	
	void SetHP(const int32 NewHP) {HP = FMath::Max(0, NewHP); UpdateHPWidget();}

	void ModifyHP(const int32 Delta) {SetHP(HP + Delta);}

	int32 GetHP() const {return HP;}

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "0"), Category="MyParams")
	int32 HP = 0;

	
	// ------ Базовые статы ------
	
public:

	int32 GetStrength() const {return Strength;}

	int32 GetAgility() const {return Agility;}

	int32 GetEndurance() const {return Endurance;}

	int32 GetWeaponDamage() const {return WeaponDamage;}

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "0"), Category="MyParams")
	int32 Strength = 0;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "0"), Category="MyParams")
	int32 Agility = 0;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "0"), Category="MyParams")
	int32 Endurance = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "0"), Category="MyParams")
	int32 WeaponDamage = 0;

	
	// ------ Особенности ------

public:

	void AddFeature() const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MyParams")
	UBonusSystemComponent* BonusSystem;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="MyParams")
	TSubclassOf<UBonusBase> BonusClass;

	
	// ------ Оружие ------

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MyParams")
	UWeapon* Weapon;


	// ------ Виджет HP ------

protected:

	void UpdateHPWidget() const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="MyParams")
	UWidgetComponent* HPWidgetComponent;

	UPROPERTY()
	UHPWidget* HPWidgetInstance;

	
	// ------ Бой ------

public:

	void PlayAttackEffect(AActor* Target, bool bHit) const;

protected:

	FVector GetAttackImpactLocation(AActor* Target, bool bHit) const;

	void SpawnAttackEffects(const FVector& Location) const;

	UPROPERTY(EditDefaultsOnly, Category = "MyParams")
	UNiagaraSystem* AttackVfx;

	UPROPERTY(EditDefaultsOnly, Category="MyParams")
	float HitVfxOffsetZ = 0.0f;

	UPROPERTY(EditDefaultsOnly, Category="MyParams")
	float HitVfxOffsetX = 0.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "MyParams", meta = (ClampMin = "0.0"))
	float MinMissRadius = 200.0f;

	UPROPERTY(EditDefaultsOnly, Category = "MyParams", meta = (ClampMin = "0.0"))
	float MaxMissRadius = 250.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "MyParams")
	USoundBase* AttackSound;

	UPROPERTY(EditDefaultsOnly, Category = "MyParams", meta = (ClampMin = "0.0", ClampMax = "2.0"))
	float AttackSoundVolume = 0.1f;
	
public:

	int32 TurnNumberInFight = 0;
};
