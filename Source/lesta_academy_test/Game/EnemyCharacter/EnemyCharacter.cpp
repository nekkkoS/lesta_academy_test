// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"

#include "Components/TextBlock.h"
#include "Components/WidgetComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
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

void AEnemyCharacter::PlayAttackEffect(AActor* Target, bool bHit) const
{
	if (!Target)
		return;

	const FVector ImpactLocation = GetAttackImpactLocation(Target, bHit);
	SpawnAttackEffects(ImpactLocation);
}

FVector AEnemyCharacter::GetAttackImpactLocation(AActor* Target, bool bHit) const
{
	if (!Target)
		return FVector::ZeroVector;

	FVector TargetLocation = Target->GetActorLocation();

	if (!bHit)
	{
		const float RandomRadius = FMath::FRandRange(MinMissRadius, MaxMissRadius);
		const float RandomAngle = FMath::FRandRange(0.f, 2 * PI);

		const FVector RandomOffset = FVector(
			FMath::Cos(RandomAngle) * RandomRadius,
			FMath::Sin(RandomAngle) * RandomRadius,
			0.f
		);

		TargetLocation += RandomOffset;
	}

	TargetLocation.Z += HitVfxOffsetZ;
	TargetLocation.X += HitVfxOffsetX;

	return TargetLocation;
}

void AEnemyCharacter::SpawnAttackEffects(const FVector& Location) const
{
	if (AttackVfx)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			GetWorld(),
			AttackVfx,
			Location,
			(Location - GetActorLocation()).Rotation()
		);
	}

	if (AttackSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			this,
			AttackSound,
			Location,
			AttackSoundVolume
		);
	}
}

