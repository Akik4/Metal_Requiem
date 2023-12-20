// Fill out your copyright notice in the Description page of Project Settings.


#include "ennemy.h"
#include <Runtime/AIModule/Classes/Perception/PawnSensingComponent.h>
#include <Runtime/AIModule/Classes/AIController.h>


// Sets default values
Aennemy::Aennemy()
{
	AutoPossessAI;
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UPawnSensingComponent* sensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("Sensing"));
	//sensing->SetSensingInterval(0.25f);
	sensing->bOnlySensePlayers = false;
	sensing->SetPeripheralVisionAngle(85.f);
	//sensing->AddToRoot();

	sensing->OnSeePawn.AddDynamic(this, &Aennemy::OnSeePawn);
	//sensing->SetPeripheralVisionAngle();

	
}

// Called when the game starts or when spawned
void Aennemy::BeginPlay()
{
	Super::BeginPlay();
	
}


void Aennemy::OnSeePawn(APawn* OtherPawn)
{
	FString message = TEXT("Saw Actor ") + OtherPawn->GetName();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, message);

	AAIController* test = GetController<AAIController>();
	test->MoveToActor(OtherPawn, 90.f);
	//test->MoveToLocation(FVector(0.f, 0.f, 0.f));

	// TODO: game-specific logic
}


// Called every frame
void Aennemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void Aennemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

