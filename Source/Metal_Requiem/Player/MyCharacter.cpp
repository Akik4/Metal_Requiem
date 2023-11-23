// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h" 
#include "GameFramework/SpringArmComponent.h" 
#include "GameFramework/PawnMovementComponent.h" 
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Setup MESH
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> Skeletal(TEXT("/Game/AnimStarterPack/UE4_Mannequin/Mesh/SK_Mannequin"));
	if (Skeletal.Succeeded())
	{
		//USkeletalMeshComponent* Mesh = GetMesh
		GetMesh()->SetSkeletalMesh(Skeletal.Object);
		GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
		//GetMesh()->SetRelativeRotation(FQuat(FVector(0, 0, 1), -1.57));
		GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationSingleNode);
	}

	static ConstructorHelpers::FObjectFinder<UAnimSequence> WalkAnimation(TEXT("/Game/AnimStarterPack/Walk_Fwd_Rifle_Ironsights"));
	if (WalkAnimation.Object != NULL)
	{
		WalkA = WalkAnimation.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimSequence> StandAnimation(TEXT("/Game/AnimStarterPack/Idle_Rifle_Hip"));
	if (StandAnimation.Object != NULL)
	{
		Stand = StandAnimation.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimSequence> SprintAnimation(TEXT("/Game/AnimStarterPack/Sprint_Fwd_Rifle"));
	if (SprintAnimation.Object != NULL)
	{
		SprintA = SprintAnimation.Object;
	}


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

bool IsWalking = false;
bool IsSprint = false;
bool Sprinting = false;
// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (!GetVelocity().IsNearlyZero()) {
		if (IsSprint)
		{
			if (!Sprinting)
			{
				GetMesh()->PlayAnimation(SprintA, true);
				GetMesh()->SetPlayRate(0.5f);
				Sprinting = true;
				IsWalking = false;
			}
		}else if (!IsWalking) {
			GetMesh()->PlayAnimation(WalkA, true);
			GetMesh()->SetPlayRate(0.5f);
			IsWalking = true;
			Sprinting = false;
		}
		
	}
	else {
		GetMesh()->PlayAnimation(Stand, true);
		GetMesh()->SetPlayRate(0.5f);
		IsWalking = false;
		Sprinting = false;
	}


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
	IsSprint = true;
}

void AMyCharacter::Walk() {
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	IsSprint = false;
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
