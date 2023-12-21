// Fill out your copyright notice in the Description page of Project Settings.


#include "character_animation.h"
#include "Player/MyCharacter.h"

Ucharacter_animation::Ucharacter_animation()
{
}

void Ucharacter_animation::NativeUpdateAnimation(float DeltaSecond)
{
	APawn* currentPawn = TryGetPawnOwner();
	if (currentPawn)
	{
		velocity = currentPawn->GetVelocity().Length();

		isFalling = currentPawn->GetMovementComponent()->IsFalling();
	}
}
