// Fill out your copyright notice in the Description page of Project Settings.



#define print(text) if(GEngine) GEngine->AddOnScreenDebugMessage(-1,1.5, FCOLOR::Green, text)
//#define printFString(text, fstring) if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FCOLOR::Green, 
//FString::Printf(Text(text), fstring))

#include "NiggerB.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

ANiggerB::ANiggerB()
{
	OnActorBeginOverlap.AddDynamic(this, &ANiggerB::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &ANiggerB::OnOverlapEnd);
	
}


void ANiggerB::BeginPlay()
{
	Super::BeginPlay();

	//DrawDebugBox(GetWorld(), GetActorLocation(), GetComponentsBoundingBox().GetExtent(), printf("Je ne suis pas une box"), true, -1, 0, 5);
}

void ANiggerB::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor && (OtherActor != this))
	{
		UE_LOG(LogTemp, Warning, TEXT("Bonhjourrr"));
		
		UGameplayStatics::OpenLevel(this, FName("test2"), true);
		
	}
}

void ANiggerB::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor && (OtherActor != this))
	{
		UE_LOG(LogTemp, Warning, TEXT("Tchao bambino"));

	}
}
