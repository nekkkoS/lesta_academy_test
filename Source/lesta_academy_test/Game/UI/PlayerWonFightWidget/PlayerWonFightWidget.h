// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerWonFightWidget.generated.h"

class UBackgroundBlur;
class UButton;
/**
 * 
 */
UCLASS()
class LESTA_ACADEMY_TEST_API UPlayerWonFightWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponChange);

	UPROPERTY(BlueprintAssignable)
	FOnWeaponChange OnWeaponChange;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnContinueGame);

	UPROPERTY(BlueprintAssignable)
	FOnContinueGame OnContinueGame;

protected:

	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

private:

	UPROPERTY(meta = (BindWidget))
	UButton* ChangeWeaponBtn;

	UPROPERTY(meta = (BindWidget))
	UButton* ContinueBtn;

	UFUNCTION()
	void OnChangeWeaponBtnClicked();

	UFUNCTION()
	void OnChangeContinueBtnClicked();
};
