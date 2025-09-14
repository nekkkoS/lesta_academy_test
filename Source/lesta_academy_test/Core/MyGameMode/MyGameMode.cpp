// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "lesta_academy_test/Core/MyHUD/MyHUD.h"
#include "lesta_academy_test/Core/MyPlayerController/MyPlayerController.h"
#include "lesta_academy_test/Game/EnemyCharacter/EnemyCharacter.h"
#include "lesta_academy_test/Game/PlayerCharacter/PlayerCharacter.h"
#include "lesta_academy_test/Game/UI/SelectCharacterClassWidget/SelectCharacterClassWidget.h"
#include "lesta_academy_test/Game/Weapon/Weapon.h"

AMyGameMode::AMyGameMode()
{
	HUDClass = AMyHUD::StaticClass();
	PlayerControllerClass = AMyPlayerController::StaticClass();


	static ConstructorHelpers::FClassFinder<USelectCharacterClassWidget> WBP_SelectCharacterClass(
		TEXT("/Game/UI/WBP_SelectCharacterClass")
	);
	if (WBP_SelectCharacterClass.Succeeded())
		SelectCharacterWidgetClass = WBP_SelectCharacterClass.Class;
}

void AMyGameMode::BeginPlay()
{
	Super::BeginPlay();

	
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PC->bShowMouseCursor = true;
	// TODO: Вернуть
	// PC->SetInputMode(FInputModeUIOnly());

	ShowSelectCharacterClass();
	StartNewGame();
}

void AMyGameMode::StartNewGame()
{
	if (!PlayerBlueprintClass || !EnemyBlueprintClass)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerBlueprintClass or EnemyBlueprintClass is not set."));
		return;
	}

	// Герой
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector PlayerLocation = FVector(0.0f, 0.0f, 100.0f);
	Player = GetWorld()->SpawnActor<APlayerCharacter>(PlayerBlueprintClass, PlayerLocation,
		FRotator::ZeroRotator, SpawnParams);
	if (!Player)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to spawn player from blueprint"));
		return;
	}
	
	Player->InitializeRandomAttributes();

	if (Player->Weapon)
	{
		FString DamageTypeString;
		switch (Player->Weapon->DamageType)
		{
		case EWeaponDamageType::Slashing:
			DamageTypeString = TEXT("Slashing");
			break;
		case EWeaponDamageType::Bludgeoning:
			DamageTypeString = TEXT("Bludgeoning");
			break;
		case EWeaponDamageType::Piercing:
			DamageTypeString = TEXT("Piercing");
			break;
		default:
			DamageTypeString = TEXT("Unknown");
			break;
		}
		
		UE_LOG(LogTemp, Warning, TEXT("Player Weapon: %s, Damage: %d, Type: %s"),
			*Player->Weapon->WeaponName.ToString(),
			Player->Weapon->BaseDamage,
			*DamageTypeString);
	}
	
	// Враг
	FVector EnemyLocation = FVector(500.0f, 0.0f, 100.0f);
	Enemy = GetWorld()->SpawnActor<AEnemyCharacter>(EnemyBlueprintClass, EnemyLocation,
		FRotator::ZeroRotator, SpawnParams);
	if (!Enemy)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to spawn enemy from blueprint"));
		return;
	}
	
	Enemy->InitializeRandomAttributes();

	if (Enemy->Weapon)
	{
		FString DamageTypeString;
		switch (Enemy->Weapon->DamageType)
		{
		case EWeaponDamageType::Slashing:
			DamageTypeString = TEXT("Slashing");
			break;
		case EWeaponDamageType::Bludgeoning:
			DamageTypeString = TEXT("Bludgeoning");
			break;
		case EWeaponDamageType::Piercing:
			DamageTypeString = TEXT("Piercing");
			break;
		default:
			DamageTypeString = TEXT("Unknown");
			break;
		}
		
		UE_LOG(LogTemp, Warning, TEXT("Enemy Weapon: %s, Damage: %d, Type: %s"),
			*Enemy->Weapon->WeaponName.ToString(),
			Enemy->Weapon->BaseDamage,
			*DamageTypeString);
	}


	StartFirstFight();
}

void AMyGameMode::StartNextFight()
{
}

void AMyGameMode::OnPlayerWonFight()
{
}

void AMyGameMode::OnPlayerLostFight()
{
}

void AMyGameMode::HandleClassSelected(const FString& CharacterClass)
{
	int x = 0;
}

void AMyGameMode::ShowSelectCharacterClass() const
{
	USelectCharacterClassWidget* SelectCharacterWidget = CreateWidget<USelectCharacterClassWidget>(
		GetWorld(), SelectCharacterWidgetClass
	);

	if (!SelectCharacterWidget)
	{
		UE_LOG(LogTemp, Error, TEXT("Create SelectCharacterWidget failed"));
		return;
	}

	SelectCharacterWidget->OnClassSelected.AddDynamic(this, &AMyGameMode::HandleClassSelected);
	SelectCharacterWidget->AddToViewport();
}

void AMyGameMode::StartFirstFight()
{
	
}
