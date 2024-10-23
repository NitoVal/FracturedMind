// Fill out your copyright notice in the Description page of Project Settings.


#include "Switch.h"

ASwitch::ASwitch()
{
	PrimaryActorTick.bCanEverTick = true;
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;

	SwitchMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SwitchMeshComponent"));
	SwitchMeshComponent->SetupAttachment(RootComponent);

	bCanBePressed = true;
}

void ASwitch::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASwitch::Interact()
{
	//Activate something
	GEngine->AddOnScreenDebugMessage(-1,5,FColor::Red,"Button has been pressed");
	bCanBePressed = false;
}

bool ASwitch::IsInteractable()
{
	return bCanBePressed;
}

