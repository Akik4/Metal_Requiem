// Fill out your copyright notice in the Description page of Project Settings.


#include "damageZone.h"
#include "Player/MyCharacter.h"

AdamageZone::AdamageZone()
{
	OnActorBeginOverlap.AddDynamic(this, &AdamageZone::OnOverlapEnter);
	OnActorEndOverlap.AddDynamic(this, &AdamageZone::OnOverlapExit);
}

void AdamageZone::BeginPlay()
{
	Super::BeginPlay();
	DrawDebugBox(GetWorld(), GetActorLocation(), GetComponentsBoundingBox().GetExtent(), FColor::Purple, true, -1, 0, 5);
}

void AdamageZone::OnOverlapEnter(class AActor* current, class AActor* player)
{

	if (player && (player != this))
	{
		AMyCharacter* user = Cast<AMyCharacter>(player);
		if (user)
		{
			user->removeHP(20.f);
		}
	}

}void AdamageZone::OnOverlapExit(class AActor* current, class AActor* player)
{
	if (player && (player != this))
	{
		AMyCharacter* user = Cast<AMyCharacter>(player);
		if (user)
		{
			user->removeHP(0.f);
		}
	}
}