// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyCharacter.generated.h"

class UWeapon;

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

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy")
	int32 Strength = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy")
	int32 Agility = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy")
	int32 Endurance = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy")
	FText UnitName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Enemy")
	int32 HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy")
	UWeapon* Weapon;

	void InitializeRandomAttributes();
};
