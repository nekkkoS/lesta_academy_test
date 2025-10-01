// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"

#include "Components/TextBlock.h"
#include "Components/WidgetComponent.h"
#include "lesta_academy_test/Game/Bonuses/BonusBase/BonusBase.h"
#include "lesta_academy_test/Game/Bonuses/BonusSystemComponent/BonusSystemComponent.h"
#include "lesta_academy_test/Game/UI/HPWidget/HPWidget.h"


// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BonusSystem = CreateDefaultSubobject<UBonusSystemComponent>(TEXT("BonusSystem"));
	HPWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPWidgetComponent"));
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	
	AddFeature();

	if (UUserWidget* Widget = HPWidgetComponent->GetWidget())
	{
		HPWidgetInstance = Cast<UHPWidget>(Widget);
		if (!HPWidgetInstance)
			UE_LOG(LogTemp, Error, TEXT("HPWidget is not assigned to HPWidgetComponent"));
	}

	UpdateHPWidget();
}

void AEnemyCharacter::AddFeature() const
{
	if (!BonusSystem || !BonusClass)
		return;
	
	BonusSystem->AddBonus(BonusClass);
}

void AEnemyCharacter::UpdateHPWidget() const
{
	if (!HPWidgetInstance)
		return;
	
	HPWidgetInstance->CurrentHP->SetText(FText::FromString(FString::Printf(TEXT("%d"), HP)));
}

