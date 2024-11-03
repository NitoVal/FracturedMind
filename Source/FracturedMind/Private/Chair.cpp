// Fill out your copyright notice in the Description page of Project Settings.

#include "Chair.h"
#include "FracturedMind/Item.h"
#include "FracturedMind/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AChair::AChair()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
    RootComponent = DefaultSceneRoot;
    
    ChairComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ChairComp"));
    ChairComp->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AChair::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AChair::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AChair::Interact()
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	this->SetActorEnableCollision(false);
	Player->Pickup(this);
}

bool AChair::IsInteractable()
{
	return true;
}

