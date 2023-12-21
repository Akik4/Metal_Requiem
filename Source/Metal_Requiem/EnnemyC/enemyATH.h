// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Player/MyCharacter.h"

#include "enemyATH.generated.h"

/**
 * 
 */
UCLASS()
class METAL_REQUIEM_API UenemyATH : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Others")
	class AMyCharacter* user;


	virtual void onRotate();
};
