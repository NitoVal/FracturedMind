// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectible.h"

#include "Components/SphereComponent.h"
#include "FracturedMind/CollectibleData.h"

// Sets default values
ACollectible::ACollectible()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;

	CollectibleMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CollectibleMeshComponent"));
	CollectibleMeshComponent->SetupAttachment(RootComponent);
	CollectibleMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	CollectibleCollision = CreateDefaultSubobject<USphereComponent>(TEXT("CollectibleCollider"));
	CollectibleCollision->SetupAttachment(DefaultSceneRoot);
	
}

// Called when the game starts or when spawned
void ACollectible::BeginPlay()
{
	Super::BeginPlay();
	if (!Collectible.IsNull())
	{
		FCollectibleData* Row = Collectible.GetRow<FCollectibleData>("Collectible Context");
		if (Row)
		{
			CollectibleMeshComponent->SetStaticMesh(Row->CollectibleModel);
			CollectibleMeshComponent->SetMaterial(0, Row->ModelMaterial);
		}

	}
}

// Called every frame
void ACollectible::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

