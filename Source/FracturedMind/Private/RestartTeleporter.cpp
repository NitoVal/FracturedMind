// Fill out your copyright notice in the Description page of Project Settings.


#include "RestartTeleporter.h"

#include "FracturedMind/PlayerCharacter.h"

// Sets default values
ARestartTeleporter::ARestartTeleporter()
{
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(RootComponent);
}

void ARestartTeleporter::BeginPlay()
{
	Super::BeginPlay();
	
}
void ARestartTeleporter::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (OtherActor->IsA(APlayerCharacter::StaticClass()) && TeleportPosition)
		OtherActor->SetActorLocation(TeleportPosition->GetActorLocation(),false,nullptr, ETeleportType::ResetPhysics);
}

