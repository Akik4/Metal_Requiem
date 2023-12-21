// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "enemyHUD.h"

#include "enemyATH.h"


#include "ennemy.generated.h"

UCLASS()
class METAL_REQUIEM_API Aennemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	Aennemy();

protected:
	float stamina;
	bool isSpriting;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnSeePawn(APawn* OtherPawn);
	UenemyHUD* widget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ATH")
	TSubclassOf<class UMyATH> athClass;

	UMyATH* ath;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ATH")
	class AMyCharacter* player;
	//TSubclassOf<class UWidgetComponent> WidgetClass;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Awareness)
	//TSubclassOf<class UPawnSensingComponent> PawnSensor;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
