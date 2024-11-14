// Fill out your copyright notice in the Description page of Project Settings.


#include "Blocker.h"

#include "FracturedMind/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABlocker::ABlocker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;

	BlockerMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockerMeshComponent"));
	BlockerMeshComponent->SetupAttachment(DefaultSceneRoot);
}

// Called when the game starts or when spawned
void ABlocker::BeginPlay()
{
	Super::BeginPlay();
	PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

// Called every frame
void ABlocker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (PlayerCharacter->Hand)
	{
		BlockerMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		BlockerMeshComponent->SetHiddenInGame(false);
	}
	else
	{
		BlockerMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		BlockerMeshComponent->SetHiddenInGame(true);
	}
}

