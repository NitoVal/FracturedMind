// Fill out your copyright notice in the Description page of Project Settings.


#include "Terminal.h"

#include "Components/WidgetComponent.h"

// Sets default values
ATerminal::ATerminal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;

	TerminalMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TerminalMeshComponent"));
	TerminalMeshComponent->SetupAttachment(RootComponent);

	TerminalWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("TerminalWidgetComponent"));
	TerminalWidgetComponent->SetupAttachment(TerminalMeshComponent);
	
	bIsInteractable = true;
}

// Called when the game starts or when spawned
void ATerminal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATerminal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATerminal::Interact()
{
	if (TerminalWidgetClass)
	{
		UUserWidget* UserWidget = CreateWidget<UUserWidget>(GetWorld(), TerminalWidgetClass);
		TerminalWidget = UserWidget;
		TerminalWidget->AddToViewport();
	}
}

bool ATerminal::IsInteractable()
{
	return bIsInteractable;
}

