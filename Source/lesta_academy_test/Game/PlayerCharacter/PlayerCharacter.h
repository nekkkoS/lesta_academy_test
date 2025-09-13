// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerCharacter.generated.h"

class UWeapon;

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

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player")
	int32 Strength = 1; // добавляется к урону
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player")
	int32 Agility = 1; // влияет на шанс попадания/провала
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player")
	int32 Endurance = 1; // даёт HP при повышении уровня

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player")
	FText UnitName;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Player")
	int32 MaxHP;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Player")
	int32 CurrentHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player")
	UWeapon* Weapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FClassLevels ClassLevels;

	void InitializeRandomAttributes();
};
