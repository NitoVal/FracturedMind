// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;

	ItemMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
	ItemMeshComponent->SetupAttachment(RootComponent);

	HoldRotation = FRotator::ZeroRotator;
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	OriginalTransform = GetActorTransform();
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::Interact()
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	this->SetActorEnableCollision(false);
	Player->Pickup(this);
}

bool AItem::IsInteractable()
{
	return true;
}

bool AItem::IsHammer()
{
	return bIsHammer;
}
