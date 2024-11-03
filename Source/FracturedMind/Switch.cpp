// Fill out your copyright notice in the Description page of Project Settings.


#include "Switch.h"

#include "PuzzleCompletionEventInterface.h"

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
	//Activate every elements
	for (AActor* Actor : Activators)
	{
		//Check if the actor has the UPuzzleCompletionEventInterface
		if (Actor && Actor->GetClass()->ImplementsInterface(UPuzzleCompletionEventInterface::StaticClass()))
		{
			IPuzzleCompletionEventInterface* InterfaceInstance = Cast<IPuzzleCompletionEventInterface>(Actor);
			if (InterfaceInstance)
				InterfaceInstance->Activate();
		}
	}
	bCanBePressed = false;
}

bool ASwitch::IsInteractable()
{
	return bCanBePressed;
}

