// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class METAL_REQUIEM_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditAnywhere);

	class UCameraComponent* Camera;
	class USpringArmComponent* CameraSpring;


	void MoveForward(float InputVector);
	void MoveSide(float InputVector);
	void Turn(float InputVector);
	void LookUp(float InputVector);
	void Sprint();
	void Walk();
	void Crouched();
	UAnimSequence* WalkA;
	UAnimSequence* Stand;
	UAnimSequence* SprintA;
	UAnimSequence* Croutch;
	bool IsMoving;


};
