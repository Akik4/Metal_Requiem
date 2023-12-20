// Fill out your copyright notice in the Description page of Project Settings.


#include "MyATH.h"

void UMyATH::UpdateStamina(float current, float max)
{
	stamina->SetPercent(current / max);
}

void UMyATH::UpdateHP(float current, float max)
{
	hp->SetPercent(current / max);
}