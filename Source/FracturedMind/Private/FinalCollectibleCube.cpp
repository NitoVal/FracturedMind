// Fill out your copyright notice in the Description page of Project Settings.


#include "FinalCollectibleCube.h" 

#include "EntitySystem/MovieSceneEntityManager.h"
#include "FracturedMind/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AFinalCollectibleCube::AFinalCollectibleCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true; 
	
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(RootComponent);
	TriggerBox->SetBoxExtent(FVector(150.f, 150.f, 100.f));  
	TriggerBox->SetCollisionProfileName(TEXT("Trigger"));

	CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
	CubeMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AFinalCollectibleCube::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFinalCollectibleCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFinalCollectibleCube::Interact()
{
	Destroy();   
}

bool AFinalCollectibleCube::IsInteractable()
{
	const APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if(PlayerCharacter->Collectibles.Num() == 6)
	{
		 return true;                         
	}
	else
	{
		return false;
	}
}
