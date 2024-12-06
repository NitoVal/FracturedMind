// Fill out your copyright notice in the Description page of Project Settings.


#include "Switch.h"

#include "PuzzleCompletionEventInterface.h"
#include "Components/AudioComponent.h"

ASwitch::ASwitch()
{
	PrimaryActorTick.bCanEverTick = true;
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;

	SwitchBaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SwitchBaseMeshComponent"));
	SwitchBaseMeshComponent->SetupAttachment(RootComponent);

	SwitchButtonMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SwitchButtonMeshComponent"));
	SwitchButtonMeshComponent->SetupAttachment(SwitchBaseMeshComponent);

	SwitchSFX = CreateDefaultSubobject<UAudioComponent>(TEXT("SwitchSFX"));
	SwitchSFX->SetupAttachment(RootComponent);

	SwitchVFX = CreateDefaultSubobject<UNiagaraComponent>(TEXT("SwitchVFX"));
	SwitchVFX->SetupAttachment(RootComponent);
	bCanBePressed = true;
}

void ASwitch::BeginPlay()
{
	Super::BeginPlay();
	SwitchButtonMeshComponent->SetMaterial(0, SwitchOffMaterial);
}

void ASwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASwitch::Interact()
{
	//Activate every element
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
	SwitchButtonMeshComponent->SetMaterial(0, SwitchOnMaterial);
	SwitchSFX->Play();
	SwitchVFX->Activate();
	bCanBePressed = false;
}

bool ASwitch::IsInteractable()
{
	return bCanBePressed;
}

void ASwitch::Activate()
{
	SwitchBaseMeshComponent->SetCollisionProfileName("BlockAllDynamic");
	SwitchButtonMeshComponent->SetCollisionProfileName("BlockAllDynamic");
	
	SetActorHiddenInGame(false);
}
