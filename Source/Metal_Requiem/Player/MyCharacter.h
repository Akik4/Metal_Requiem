// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h" 
#include "GameFramework/SpringArmComponent.h" 
#include "GameFramework/PawnMovementComponent.h" 
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine.h"
#include "../../../../../../../../Program Files/Epic Games/UE_5.3/Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "../../../../../../../../Program Files/Epic Games/UE_5.3/Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "Metal_Requiem/MyATH.H"
#include <Metal_Requiem/character_animation.h>


#include "MyCharacter.generated.h"

UCLASS()
class METAL_REQUIEM_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();
	bool isJumping;

protected:
	// Called when the game starts or when spawned
	bool isSprinting;
	bool isWalking;
	float isTakingDamage;
	float stamina;
	float healpoint;

	virtual void BeginPlay() override;
	virtual void move(const FInputActionValue& value);
	virtual void turn(const FInputActionValue& value);
	virtual void sprint();
	virtual void OnJumpPressed();
	APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void removeHP(float hp);
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditAnywhere);

	class UCameraComponent* Camera;
	class USpringArmComponent* CameraSpring;

	UPROPERTY(EditAnywhere, BLueprintReadOnly, Category = "Input management")
	class UInputMappingContext* InputMapping;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input management")
	class UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input management")
	class UInputAction* LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input management")
	class UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input management")
	class UInputAction* SprintAction;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ATH")
	TSubclassOf<class UMyATH> PlayerHUDClass;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animationss")
	class UAnimMontage* jumpAnimation;


	class Ucharacter_animation* tests = Cast<Ucharacter_animation>(GetMesh()->GetAnimInstance());
	class UMyATH* PlayerHUD;
};
