// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h" 
#include "GameFramework/SpringArmComponent.h" 
#include "GameFramework/PawnMovementComponent.h" 
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// Create a camera element with position and control
	CameraSpring = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpring"));
	CameraSpring->SetupAttachment(RootComponent);
	CameraSpring->TargetArmLength = 300.f;
	CameraSpring->SetRelativeLocation(FVector(0.f, 0.f, 100.f));
	CameraSpring->bUsePawnControlRotation = true;


	//Create the used camera in the game with Camera spring settings
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	Camera->SetupAttachment(CameraSpring);

	GetCharacterMovement()->MaxWalkSpeed = 500.f;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AMyCharacter::Sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AMyCharacter::Walk);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AMyCharacter::Crouched);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AMyCharacter::Walk);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveSide", this, &AMyCharacter::MoveSide);

	PlayerInputComponent->BindAxis("Turn", this, &AMyCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &AMyCharacter::LookUp);

}

void AMyCharacter::MoveForward(float InputVector) {


	// Get the current Direction to move -> In this case Forward or Backward
	FVector World = GetActorForwardVector();

	AddMovementInput(World, InputVector);

}

void AMyCharacter::MoveSide(float InputVector)
{
	// Get the current Direction to move -> In this case Right or left
	FVector World = GetActorRightVector();

	AddMovementInput(World, InputVector);
}

void AMyCharacter::Sprint() {
	GetCharacterMovement()->MaxWalkSpeed = 1000.f;
}

void AMyCharacter::Walk() {
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
}

void AMyCharacter::Crouched() {
	GetCharacterMovement()->MaxWalkSpeed = 250.f;
}


void AMyCharacter::Turn(float InputVector)
{
	// Yaw mean right or left
	AddControllerYawInput(InputVector);
}

void AMyCharacter::LookUp(float InputVector)
{
	// Pitch mean Up or Down
	AddControllerPitchInput(InputVector);
}
