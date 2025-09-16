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

	ShowSelectCharacterClassWidget();
	StartNewGame();
}

void AMyGameMode::StartNewGame()
{
	if (!PlayerBlueprintClass)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerBlueprintClass is not set."));
		return;
	}

	// Герой
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	FVector PlayerLocation = FVector(100.0f, 0.0f, 100.0f);
	Player = GetWorld()->SpawnActor<APlayerCharacter>(PlayerBlueprintClass, PlayerLocation,
		FRotator::ZeroRotator, SpawnParams);
	if (!Player)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to spawn player from blueprint"));
		return;
	}
	
	Player->InitializeRandomAttributes();

	
	// Враг (рандомный)
	SpawnRandomEnemy(SpawnParams);


	SimulateFights();
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

// TODO: Заменить строку на enum
void AMyGameMode::HandleClassSelected(const FString& CharacterClass)
{
	if (CharacterClass == "Rogue")
		Player->ClassLevels.Rogue++;
	else if (CharacterClass == "Warrior")
		Player->ClassLevels.Warrior++;
	else if (CharacterClass == "Barbarian")
		Player->ClassLevels.Barbarian++;
}

void AMyGameMode::SpawnRandomEnemy(const FActorSpawnParameters& SpawnParams)
{
	// TODO: чекнуть есть ли проверка на пустой массив
	
	// выбираем случайный класс врага
	int32 Index = FMath::RandRange(0, EnemyBlueprintClasses.Num() - 1);
	TSubclassOf<AEnemyCharacter> EnemyClass = EnemyBlueprintClasses[Index];

	FVector EnemyLocation = FVector(500.0f, 0.0f, 100.0f);
	Enemy = GetWorld()->SpawnActor<AEnemyCharacter>(
		EnemyClass,
		EnemyLocation,
		FRotator::ZeroRotator,
		SpawnParams
	);

	if (!Enemy)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to spawn enemy from blueprint"));
		return;
	}

	Enemy->InitializeRandomAttributes();

	UE_LOG(LogTemp, Warning, TEXT("Spawned enemy of class: %s"), *Enemy->GetClass()->GetName());
}

void AMyGameMode::ShowSelectCharacterClassWidget() const
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

void AMyGameMode::SimulateFights()
{
	if (!Player || !Enemy)
	{
		UE_LOG(LogTemp, Error, TEXT("No Player or Enemy to start fight."));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("=== Fight Started ==="));
	UE_LOG(LogTemp, Warning, TEXT("Player HP: %d | Enemy HP: %d"), Player->GetHP(), Enemy->GetHP());
	
	bool bPlayerTurn = Player->GetAgility() >= Enemy->GetAgility();
	while (Player->GetHP() > 0 && Enemy->GetHP() > 0)
	{
		if (bPlayerTurn)  // Ходит игрок, Enemy цель
		{
			if (FMath::RandRange(1, Player->GetAgility() + Enemy->GetAgility()) <= Enemy->GetAgility())
			{
				UE_LOG(LogTemp, Warning, TEXT("Player missed the attack!"));
			}
			else
			{
				int32 Damage = Player->GetStrength() + (Player->Weapon ? Player->Weapon->BaseDamage : 0);
				Enemy->ModifyHP(-Damage);
				UE_LOG(LogTemp, Warning, TEXT("Player hits Enemy for %d damage! Enemy HP: %d"), Damage,
					Enemy->GetHP());
			}
		}
		else  // Ходит Enemy, игрок цель
		{
			if (FMath::RandRange(1, Player->GetAgility() + Enemy->GetAgility()) <= Player->GetAgility())
			{
				UE_LOG(LogTemp, Warning, TEXT("Enemy missed the attack!"));
			}
			else
			{
				int32 Damage = Enemy->GetStrength() + Enemy->WeaponDamage;
				Player->ModifyHP(-Damage);
			}
		}
		UE_LOG(LogTemp, Warning, TEXT("Player HP: %d | Enemy HP: %d"), Player->GetHP(), Enemy->GetHP());
		
		bPlayerTurn = !bPlayerTurn;
	}
	
	if (Player->GetHP() > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("=== Player Won the Fight! ==="));
		OnPlayerWonFight();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("=== Enemy Won the Fight! ==="));
		OnPlayerLostFight();
	}
}
