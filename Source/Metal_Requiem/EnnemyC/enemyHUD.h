// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "enemyATH.h"

#include "enemyHUD.generated.h"

/**
 * 
 */
UCLASS()
class METAL_REQUIEM_API UenemyHUD : public UWidgetComponent
{
	GENERATED_BODY()

public:
	UenemyHUD();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Displayed")
	TSubclassOf<class UUserWidget> enemyHUDClass;

	TSubclassOf<class UMyATH> WidgetClass;
	
};
