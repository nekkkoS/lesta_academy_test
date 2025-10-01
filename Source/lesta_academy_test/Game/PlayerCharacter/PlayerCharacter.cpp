// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "Components/TextBlock.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "lesta_academy_test/Core/MyHUD/MyHUD.h"
#include "lesta_academy_test/Game/Bonuses/BonusBase/BonusBase.h"
#include "lesta_academy_test/Game/Bonuses/BonusSystemComponent/BonusSystemComponent.h"
#include "lesta_academy_test/Game/UI/HPWidget/HPWidget.h"
#include "lesta_academy_test/Game/UI/HUDWidget/HUDWidget.h"
#include "lesta_academy_test/Game/UI/SelectedClassesWidget/SelectedClassesWidget.h"
#include "lesta_academy_test/Game/Weapon/Weapon.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BonusSystem = CreateDefaultSubobject<UBonusSystemComponent>(TEXT("BonusSystem"));
	HPWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPWidgetComponent"));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();


	if (UUserWidget* Widget = HPWidgetComponent->GetWidget())
	{
		HPWidgetInstance = Cast<UHPWidget>(Widget);
		if (!HPWidgetInstance)
			UE_LOG(LogTemp, Error, TEXT("HPWidget is not assigned to HPWidgetComponent"));
	}

	UpdateHPWidget();
}

void APlayerCharacter::UpdateLevel(const ECharacterClass ClassForUpLevel)
{
	switch (ClassForUpLevel)
	{
	case ECharacterClass::Rogue:     ClassLevels.Rogue++; break;
	case ECharacterClass::Warrior:   ClassLevels.Warrior++; break;
	case ECharacterClass::Barbarian: ClassLevels.Barbarian++; break;
	default: return;
	}
	
	if (!BonusSystem || !ClassParamsTable)
	{
		UE_LOG(LogTemp, Error, TEXT("BonusSystem or ClassParamsTable is null"));
		return;
	}

	// Сбрасываем HP + бонусы и выставляем заново
	SetMaxHP(0);
	BonusSystem->RemoveAllBonuses();

	TArray<FClassParamsRow*> Rows;
	ClassParamsTable->GetAllRows(TEXT("ClassParams Lookup"), Rows);

	for (const auto* Row : Rows)
	{
		int32 Level = 0;

		switch (Row->Class)
		{
		case ECharacterClass::Rogue:     Level = ClassLevels.Rogue; break;
		case ECharacterClass::Warrior:   Level = ClassLevels.Warrior; break;
		case ECharacterClass::Barbarian: Level = ClassLevels.Barbarian; break;
		default: break;
		}

		if (Level <= 0) continue;

		// HP за каждый уровень
		ModifyMaxHP(Row->HPPerLevel * Level);

		// Начальное оружие (если ещё нет)
		if (Level >= 1 && !Weapon && Row->DefaultWeapon)
		{
			Weapon = Row->DefaultWeapon;
			UE_LOG(LogTemp, Log, TEXT("Weapon set to %s"), *Weapon->WeaponName.ToString());
		}
		
		if (Level >= 1 && Row->BonusAtLevel1) BonusSystem->AddBonus(Row->BonusAtLevel1);
		if (Level >= 2 && Row->BonusAtLevel2) BonusSystem->AddBonus(Row->BonusAtLevel2);
		if (Level >= 3 && Row->BonusAtLevel3) BonusSystem->AddBonus(Row->BonusAtLevel3);
	}

	// Обновляем значения выбранных классов в виджете
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!PC)
	{
		UE_LOG(LogTemp, Error, TEXT("Error getting PlayerController"));
		return;
	}

	AMyHUD* HUD = Cast<AMyHUD>(PC->GetHUD());
	if (!HUD)
	{
		UE_LOG(LogTemp, Error, TEXT("Error getting HUD"));
		return;
	}

	UHUDWidget* HUDWidget = HUD->GetHUDWidget();
	if (!HUDWidget)
	{
		UE_LOG(LogTemp, Error, TEXT("Error getting HUDWidget"));
		return;
	}

	HUDWidget->SelectedClassesWidget->UpdateClassLevels(ClassLevels);
	

	TotalPlayerCharacterLevel++;
	ModifyMaxHP(GetEndurance() * TotalPlayerCharacterLevel);
}

void APlayerCharacter::UpdateHPWidget() const
{
	if (!HPWidgetInstance)
		return;
	
	HPWidgetInstance->CurrentHP->SetText(FText::FromString(FString::Printf(TEXT("%d"), HP)));
}

void APlayerCharacter::InitializeRandomAttributes()
{
	Strength = FMath::RandRange(1, 3);
	Agility = FMath::RandRange(1, 3);
	Endurance = FMath::RandRange(1, 3);

	UE_LOG(LogTemp, Warning, TEXT("PlayerCharacter attributes initialized:"));
	UE_LOG(LogTemp, Warning, TEXT("Strength: %d"), Strength);
	UE_LOG(LogTemp, Warning, TEXT("Agility: %d"), Agility);
	UE_LOG(LogTemp, Warning, TEXT("Endurance: %d"), Endurance);
}

