// Fill out your copyright notice in the Description page of Project Settings.


#include "ennemy.h"
#include <Runtime/AIModule/Classes/Perception/PawnSensingComponent.h>
#include <Runtime/AIModule/Classes/AIController.h>
#include <Components/WidgetComponent.h>
#include "Math/UnrealMathUtility.h" 
#include <Kismet/KismetMathLibrary.h>

// Sets default values
Aennemy::Aennemy()
{
	AutoPossessAI;
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	stamina = 100.f;
	isSpriting = false;

	UPawnSensingComponent* sensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("Sensing"));
	//sensing->SetSensingInterval(0.25f);
	sensing->bOnlySensePlayers = false;
	sensing->SetPeripheralVisionAngle(85.f);
	//sensing->AddToRoot();
	sensing->OnSeePawn.AddDynamic(this, &Aennemy::OnSeePawn);



	widget = CreateDefaultSubobject<UenemyHUD>(TEXT("WidgetATH"));
	widget->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void Aennemy::BeginPlay()
{
	Super::BeginPlay();;
	widget->SetWidgetClass(athClass);
	widget->InitWidget();

	ath = Cast<UMyATH>(widget->GetWidget());

	
}


void Aennemy::OnSeePawn(APawn* OtherPawn)
{
	player = Cast<AMyCharacter>(OtherPawn);
	FString message = TEXT("Saw Actor ") + OtherPawn->GetName();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, message);

	AAIController* ennemyController = GetController<AAIController>();
	ennemyController->MoveToActor(OtherPawn, 90.f);
	
	FVector PlayerLocation = OtherPawn->GetActorLocation();
	FVector ennemyLocation = GetActorLocation();

	double distance = sqrt(pow(PlayerLocation.X - ennemyLocation.X, 2) + pow(PlayerLocation.Y - ennemyLocation.Y, 2));

	FString messages = FString::SanitizeFloat(distance);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, messages, false);
	if (distance > 500.00)
	{
		if (stamina > 0)
		{
			GetCharacterMovement()->MaxWalkSpeed = 1400.f;
			isSpriting = true;
		}
		else {
			GetCharacterMovement()->MaxWalkSpeed = 300.f;
		}
	}
	else {
		GetCharacterMovement()->MaxWalkSpeed = 600.F;
		isSpriting = false;
	}
	//test->MoveToLocation(FVector(0.f, 0.f, 0.f));

	// TODO: game-specific logic
}


// Called every frame
void Aennemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (player)
	{
		//FRotator test = FMath::RInterpTo(GetActorRotation(), player->GetActorRotation(), DeltaTime, 1.f);
		FRotator PlayerRot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), player->GetActorLocation());
		widget->SetWorldRotation(PlayerRot);

	}


	UE_LOG(LogTemp, Warning, TEXT("Je suis %s"), ath);
	if (ath)
	{
		ath->UpdateStamina(stamina, 100.f);
	}


	if (isSpriting) {
		if (stamina > 0)
		{
			stamina -= 20 * DeltaTime;
		}
	}
	else {
		stamina += 5 * DeltaTime;
	}

}



// Called to bind functionality to input
void Aennemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

