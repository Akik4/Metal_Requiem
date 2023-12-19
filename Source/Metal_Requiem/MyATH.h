// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "MyATH.generated.h"

/**
 * 
 */
UCLASS()
class METAL_REQUIEM_API UMyATH : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void UpdateStamina(float current, float max);

protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UProgressBar* stamina;
};
