// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "lesta_academy_test/Core/MyHUD/MyHUD.h"
#include "lesta_academy_test/Core/MyPlayerController/MyPlayerController.h"
#include "lesta_academy_test/Game/PlayerCharacter/PlayerCharacter.h"
#include "lesta_academy_test/Game/UI/SelectCharacterClassWidget/SelectCharacterClassWidget.h"

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

	StartNewGame();
}

void AMyGameMode::StartNewGame()
{
	Player = GetWorld()->SpawnActor<APlayerCharacter>();
	UE_LOG(LogTemp, Warning, TEXT("StartNewGame. Player spawned."));
	Player->InitializeRandomAttributes();
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
