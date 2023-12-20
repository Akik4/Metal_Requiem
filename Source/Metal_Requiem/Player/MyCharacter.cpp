// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer;
	isWalking = false;
	isSprinting = false;
	stamina = 100.f;
	healpoint = 100.f;
	isTakingDamage = 0.f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);

	CameraSpring = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpring"));
	CameraSpring->SetupAttachment(RootComponent);
	CameraSpring->TargetArmLength = 300.f;
	CameraSpring->bUsePawnControlRotation = true;


	//Create the used camera in the game with Camera spring settings
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	Camera->SetupAttachment(CameraSpring);
	Camera->bUsePawnControlRotation = false;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Create a camera element with position and control

	GetCharacterMovement()->MaxWalkSpeed = 500.f;

	APlayerController* me = GetController<APlayerController>();
	PlayerHUD = CreateWidget<UMyATH>(me, PlayerHUDClass);

	PlayerHUD->AddToPlayerScreen();

}
// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (healpoint <= 0)
	{
		GetMesh()->SetSimulatePhysics(true);
	}

	if (isTakingDamage != 0.f)
	{
		healpoint -= isTakingDamage * DeltaTime;
	}

	PlayerHUD->UpdateStamina(stamina, 100.f);
	PlayerHUD->UpdateHP(healpoint, 100.f);

	if (isSprinting)
	{
		if (GetVelocity().Length() > 0)
		{
			if (stamina >= 0)
			{
				stamina -= 20 * DeltaTime;
				GetCharacterMovement()->MaxWalkSpeed = 1500.f;
			}
			else {
				GetCharacterMovement()->MaxWalkSpeed = 300.f;
			}
		}
	}

	if (!isSprinting || GetVelocity().Length() == 0)
	{
		if (stamina <= 100)
		{
			stamina += 10 * DeltaTime;
		}
		GetCharacterMovement()->MaxWalkSpeed = 500.f;
	}
	//FString test = TEXT("Bonjour") + GetVelocity().Length();
	//UE_LOG(LogTemp, Warning, TEXT("%lld"), GetVelocity().Length());
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	APlayerController* PC = Cast<APlayerController>(GetController());

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());

	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMapping, 0);

	if (UEnhancedInputComponent* PlayerEnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		PlayerEnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyCharacter::move);
		PlayerEnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyCharacter::turn);
		PlayerEnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMyCharacter::jump);
		PlayerEnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &AMyCharacter::sprint);
		PlayerEnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AMyCharacter::sprint);

	}
}


void AMyCharacter::move(const FInputActionValue& Value)
{
	const FVector2D MoveValue = Value.Get<FVector2D>();

	if (MoveValue.Y != 0.f)
	{
		// find out which way is forward
		const FRotator Rotation = controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, MoveValue.Y);
	}
	if (MoveValue.X != 0.f)
	{
		const FRotator Rotation = controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, MoveValue.X);
	}
}

void AMyCharacter::turn(const FInputActionValue& Value)
{
	const FVector2D value = Value.Get<FVector2D>();

	if (value.Y != 0.f)
	{
		AddControllerPitchInput(-value.Y * 15.f * GetWorld()->GetDeltaSeconds());
	}
	if (value.X != 0.f)
	{
		AddControllerYawInput(value.X * 15.f * GetWorld()->GetDeltaSeconds());
	}
}

void AMyCharacter::sprint()
{
	isSprinting = !isSprinting;
}

void AMyCharacter::jump()
{
	Jump();
}

void AMyCharacter::removeHP(float heal)
{
	isTakingDamage = heal;
}
