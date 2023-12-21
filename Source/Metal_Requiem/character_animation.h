// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "character_animation.generated.h"

/**
 * 
 */
UCLASS()
class METAL_REQUIEM_API Ucharacter_animation : public UAnimInstance
{
	GENERATED_BODY()


public:
	Ucharacter_animation();
	UPROPERTY(BlueprintReadWrite)
	float velocity;
	UPROPERTY(BlueprintReadWrite)
	bool isFalling;
	UPROPERTY(BlueprintReadWrite)
	bool startJumping = false;

protected:
	virtual void NativeUpdateAnimation(float DeltaSecond) override;
	
};
