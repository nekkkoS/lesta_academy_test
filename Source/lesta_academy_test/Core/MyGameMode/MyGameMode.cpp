// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "lesta_academy_test/Core/MyHUD/MyHUD.h"
#include "lesta_academy_test/Core/MyPlayerController/MyPlayerController.h"

AMyGameMode::AMyGameMode()
{
	HUDClass = AMyHUD::StaticClass();
	PlayerControllerClass = AMyPlayerController::StaticClass();
}

void AMyGameMode::BeginPlay()
{
	Super::BeginPlay();

	
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PC->bShowMouseCursor = true;
}
