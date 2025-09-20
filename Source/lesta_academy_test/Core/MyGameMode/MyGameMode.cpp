// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "lesta_academy_test/Core/MyHUD/MyHUD.h"
#include "lesta_academy_test/Core/MyPlayerController/MyPlayerController.h"
#include "lesta_academy_test/Game/Bonuses/BonusSystemComponent/BonusSystemComponent.h"
#include "lesta_academy_test/Game/EnemyCharacter/EnemyCharacter.h"
#include "lesta_academy_test/Game/PlayerCharacter/PlayerCharacter.h"
#include "lesta_academy_test/Game/UI/SelectCharacterClassWidget/SelectCharacterClassWidget.h"
#include "lesta_academy_test/Game/UI/PlayerLostFightWidget/PlayerLostFightWidget.h"
#include "lesta_academy_test/Game/UI/PlayerWonFightWidget/PlayerWonFightWidget.h"
#include "lesta_academy_test/Game/UI/EndOfGameWidget/EndOfGameWidget.h"
#include "lesta_academy_test/Game/Weapon/Weapon.h"

AMyGameMode::AMyGameMode()
{
	HUDClass = AMyHUD::StaticClass();
	PlayerControllerClass = AMyPlayerController::StaticClass();


	static ConstructorHelpers::FClassFinder<USelectCharacterClassWidget> WBP_SelectCharacter(
		TEXT("/Game/UI/WBP_SelectCharacterClass")
	);
	if (WBP_SelectCharacter.Succeeded())
		SelectCharacterWidgetClass = WBP_SelectCharacter.Class;

	static ConstructorHelpers::FClassFinder<UPlayerLostFightWidget> WBP_PlayerLostFight(
		TEXT("/Game/UI/WBP_PlayerLostFight")
	);
	if (WBP_PlayerLostFight.Succeeded())
		PlayerLostFightWidgetClass = WBP_PlayerLostFight.Class;

	static ConstructorHelpers::FClassFinder<UPlayerWonFightWidget> WBP_PlayerWonFight(
		TEXT("/Game/UI/WBP_PlayerWonFight")
	);
	if (WBP_PlayerWonFight.Succeeded())
		PlayerWonFightWidgetClass = WBP_PlayerWonFight.Class;

	static ConstructorHelpers::FClassFinder<UEndOfGameWidget> WBP_EndOfGame(
		TEXT("/Game/UI/WBP_EndOfGame")
	);
	if (WBP_EndOfGame.Succeeded())
		EndOfGameWidgetClass = WBP_EndOfGame.Class;
}

void AMyGameMode::BeginPlay()
{
	Super::BeginPlay();

	
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PC->bShowMouseCursor = true;
	// PC->SetInputMode(FInputModeUIOnly());
	
	StartNewGame();
}

void AMyGameMode::StartNewGame()
{
	if (!PlayerBlueprintClass)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerBlueprintClass is not set."));
		return;
	}
	
	if (!SpawnPlayerCharacter())
		return;
	Player->Init();
	
	if (!SpawnRandomEnemy())
		return;
	Enemy->InitializeRandomAttributes();

	ShowSelectCharacterClassWidget();
}

bool AMyGameMode::SpawnPlayerCharacter()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	FVector PlayerLocation = FVector(100.0f, 0.0f, 100.0f);
	Player = GetWorld()->SpawnActor<APlayerCharacter>(PlayerBlueprintClass, PlayerLocation,
		FRotator::ZeroRotator, SpawnParams);
	
	if (!Player)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to spawn player from blueprint"));
		return false;
	}

	return true;
}

bool AMyGameMode::SpawnRandomEnemy()
{
	if (EnemyClassesSample.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("EnemyClassesSample is empty."));
		return false;
	}
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	int32 Index = FMath::RandRange(0, EnemyClassesSample.Num() - 1);
	TSubclassOf<AEnemyCharacter> EnemyClass = EnemyClassesSample[Index];
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
		return false;
	}

	UE_LOG(LogTemp, Warning, TEXT("Spawned enemy of class: %s"), *Enemy->GetClass()->GetName());
	return true;
}

void AMyGameMode::ShowSelectCharacterClassWidget() const
{
	USelectCharacterClassWidget* SelectCharacterWidget = CreateWidget<USelectCharacterClassWidget>(
		GetWorld(), SelectCharacterWidgetClass
	);

	if (!SelectCharacterWidget)
	{
		UE_LOG(LogTemp, Error, TEXT("Fail to create SelectCharacterWidget"));
		return;
	}

	SelectCharacterWidget->OnClassSelected.AddDynamic(this, &AMyGameMode::HandleClassSelected);
	SelectCharacterWidget->AddToViewport();
}

// TODO: Заменить строку на enum
void AMyGameMode::HandleClassSelected(const FString& CharacterClass)
{
	if (!Player)
	{
		UE_LOG(LogTemp, Error, TEXT("Player is not initialized."));
		return;
	}
	
	if (CharacterClass == "Rogue")
		Player->ClassLevels.Rogue++;
	else if (CharacterClass == "Warrior")
		Player->ClassLevels.Warrior++;
	else if (CharacterClass == "Barbarian")
		Player->ClassLevels.Barbarian++;

	// Player->UpdateHP();
	Player->AddBonuses();
	
	StartFight();
}

void AMyGameMode::StartFight()
{
	if (!Player || !Enemy || !Player->Weapon || !Enemy->Weapon)
	{
		UE_LOG(LogTemp, Error, TEXT("Player or Enemy is not ready start fight."));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("=== Fight Started ==="));
	UE_LOG(LogTemp, Warning, TEXT("Player HP: %d | Enemy HP: %d"), Player->GetHP(), Enemy->GetHP());
	UE_LOG(LogTemp, Warning, TEXT("Player weapon: %s | Enemy weapon: %s"),
		*Player->Weapon->WeaponName.ToString(), *Enemy->Weapon->WeaponName.ToString());
	
	bPlayerTurn = Player->GetAgility() >= Enemy->GetAgility();
	
	GetWorldTimerManager().SetTimer(FightTurnTimer, this, &AMyGameMode::DoTurn, 1.0f, false);
}

void AMyGameMode::DoTurn()
{
	Enemy->SetHP(0);
	if (Player->GetHP() == 0 || Enemy->GetHP() == 0)
	{
		if (Player->GetHP() > 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("=== Player Won the Fight! ==="));
			OnPlayerWonFight();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("=== Enemy Won the Fight! ==="));
			ShowPlayerLostFightWidget();
		}
		return;
	}

	// UE_LOG(LogTemp, Warning, TEXT("=== Next turn ==="));
	//
	// if (bPlayerTurn)
	// {
	// 	if (FMath::RandRange(1, Player->GetAgility() + Enemy->GetAgility()) <= Enemy->GetAgility())
	// 	{
	// 		UE_LOG(LogTemp, Warning, TEXT("Player missed the attack!"));
	// 	}
	// 	else
	// 	{
	// 		/*const int32 Damage = CalculateFight(Player, Enemy, true);
	// 		UE_LOG(LogTemp, Warning, TEXT("Player attack Enemy on %i damage"), Damage);
	// 		UE_LOG(LogTemp, Warning, TEXT("Current Enemy HP: %i"), Enemy->GetHP());*/
	// 		
	// 		Enemy->ModifyHP(-1);
	// 		UE_LOG(LogTemp, Warning, TEXT("After Damage Enemy HP: %i"), Enemy->GetHP());
	// 	}
	// }
	// else
	// {
	// 	if (FMath::RandRange(1, Player->GetAgility() + Enemy->GetAgility()) <= Player->GetAgility())
	// 	{
	// 		UE_LOG(LogTemp, Warning, TEXT("Enemy missed the attack!"));
	// 	}
	// 	else
	// 	{
	// 		/*const int32 Damage = CalculateFight(Player, Enemy, false);
	// 		UE_LOG(LogTemp, Warning, TEXT("Enemy attack Player on %i damage"), Damage);
	// 		UE_LOG(LogTemp, Warning, TEXT("Current Player HP: %i"), Enemy->GetHP());*/
	// 		
	// 		Enemy->ModifyHP(-1);
	// 		UE_LOG(LogTemp, Warning, TEXT("After Damage Player HP: %i"), Enemy->GetHP());
	// 	}
	// }
	//
	// bPlayerTurn = !bPlayerTurn;
	//
	// GetWorldTimerManager().SetTimer(FightTurnTimer, this, &AMyGameMode::DoTurn, 0.1f, false);
}

int32 AMyGameMode::CalculateFight(const APlayerCharacter* InPlayer, const AEnemyCharacter* InEnemy,
	const bool IsPlayerTurn)
{
	if (IsPlayerTurn)
	{
		FFightInfo FightInfo = {
			0,
			InPlayer->GetStrength(),
			InPlayer->GetAgility(),
			InPlayer->GetEndurance(),
			InPlayer->Weapon->BaseDamage,
			InPlayer->Weapon->DamageType,
			
			InEnemy->GetStrength(),
			InEnemy->GetAgility(),
			InEnemy->GetEndurance(),
			InEnemy->WeaponDamage,
			0
		};

		// Обязательно! Сначала применяются все бонусы атакующего, затем защищающегося.
		InPlayer->BonusSystem->ApplyBonuses(FightInfo);
		FightInfo.AttackerTotalDamage = FightInfo.AttackerStrength + FightInfo.AttackerWeaponDamage + FightInfo.Damage;
		// InEnemy->BonusSystem->ApplyBonuses(FightInfo);
		
		
		return FightInfo.AttackerTotalDamage;
	}
	

	return 0;
}

void AMyGameMode::ShowPlayerLostFightWidget() const
{
	UPlayerLostFightWidget* PlayerLostFightWidget = CreateWidget<UPlayerLostFightWidget>(
		GetWorld(), PlayerLostFightWidgetClass
	);

	if (!PlayerLostFightWidget)
	{
		UE_LOG(LogTemp, Error, TEXT("Fail to create PlayerLostFightWidget"));
		return;
	}
	
	PlayerLostFightWidget->AddToViewport();
}

void AMyGameMode::OnPlayerWonFight()
{
	ConsecutiveWins++;
	if (ConsecutiveWins == 5)
	{
		ShowEndOfGameWidget();
		return;
	}

	ShowPlayerWonFightWidget();
}

void AMyGameMode::ShowPlayerWonFightWidget() const
{
	UPlayerWonFightWidget* PlayerWonFightWidget = CreateWidget<UPlayerWonFightWidget>(
		GetWorld(), PlayerWonFightWidgetClass
	);

	if (!PlayerWonFightWidget)
	{
		UE_LOG(LogTemp, Error, TEXT("Fail to create PlayerWonFightWidget"));
		return;
	}
	
	PlayerWonFightWidget->OnWeaponChange.AddDynamic(this, &AMyGameMode::OnPlayerChangeWeapon);
	PlayerWonFightWidget->AddToViewport();
}

void AMyGameMode::ShowEndOfGameWidget() const
{
	UEndOfGameWidget* EndOfGameWidget = CreateWidget<UEndOfGameWidget>(
		GetWorld(), EndOfGameWidgetClass
	);

	if (!EndOfGameWidget)
	{
		UE_LOG(LogTemp, Error, TEXT("Fail to create EndOfGameWidget"));
		return;
	}
	
	EndOfGameWidget->AddToViewport();
}

void AMyGameMode::OnPlayerChangeWeapon()
{
	if (Player && Enemy && Enemy->Weapon)
	{
		Player->Weapon = Enemy->Weapon;
		UE_LOG(LogTemp, Warning, TEXT("Player changed weapon to: %s"), *Player->Weapon->GetName());
	}
}
