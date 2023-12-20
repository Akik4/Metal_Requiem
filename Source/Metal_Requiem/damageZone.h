// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "DrawDebugHelpers.h"
#include "damageZone.generated.h"

/**
 * 
 */
UCLASS()
class METAL_REQUIEM_API AdamageZone : public ATriggerBox
{
	GENERATED_BODY()

public: 
	AdamageZone();

	UFUNCTION() 
		void OnOverlapEnter(class AActor* overlappedActor, class AActor* OtherActor);
	
	UFUNCTION() 
		void OnOverlapExit(class AActor* overlappedActor, class AActor* OtherActor);
	
	
protected:
	virtual void BeginPlay() override;
};
