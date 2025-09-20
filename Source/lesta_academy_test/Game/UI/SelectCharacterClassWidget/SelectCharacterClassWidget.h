// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SelectCharacterClassWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class LESTA_ACADEMY_TEST_API USelectCharacterClassWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnClassSelected, ECharacterClass, CharacterClass);

	UPROPERTY(BlueprintAssignable)
	FOnClassSelected OnClassSelected;

protected:

	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

private:

	UPROPERTY(meta = (BindWidget))
	UButton* RogueBtn;

	UPROPERTY(meta = (BindWidget))
	UButton* WarriorBtn;

	UPROPERTY(meta = (BindWidget))
	UButton* BarbarianBtn;

	UFUNCTION()
	void OnRogueBtnClicked();

	UFUNCTION()
	void OnWarriorBtnClicked();

	UFUNCTION()
	void OnBarbarianBtnClicked();
};
