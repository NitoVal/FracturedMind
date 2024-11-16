// Fill out your copyright notice in the Description page of Project Settings.


#include "Breakable.h"

#include "Item.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABreakable::ABreakable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;
	
	RequiredTag = "";
}

// Called when the game starts or when spawned
void ABreakable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABreakable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABreakable::Interact()
{
	const APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (PlayerCharacter->Hand)
	{
		if (PlayerCharacter->Hand->Tags.Contains(RequiredTag))
			Destroy();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1,5, FColor::Red,"Can't Break");
	}
}

bool ABreakable::IsInteractable()
{
	return true;
}

