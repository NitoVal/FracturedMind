// Fill out your copyright notice in the Description page of Project Settings.


#include "BigItems.h"
#include "FracturedMind/Item.h"
#include "FracturedMind/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABigItems::ABigItems()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	BigItemComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BigItemComp"));
	BigItemComp->SetupAttachment(RootComponent); 
}

// Called when the game starts or when spawned
void ABigItems::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABigItems::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABigItems::Interact()
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	this->SetActorEnableCollision(false);
	Player->PickupBigItem(this);
}

bool ABigItems::IsInteractable()
{
	return true;
}
