// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

#include "PlayerCharacter.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;
	
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetBoxExtent(FVector(128,128,128));
	TriggerBox->SetupAttachment(RootComponent);
	
	DoorMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMeshComponent->SetupAttachment(RootComponent);
	
	LockMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LockMesh"));
	LockMeshComponent->SetupAttachment(DoorMeshComponent);
	
	bIsUnlocked = false;
	bIsOpen = false; 

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ADoor::OnBeginOverlap);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ADoor::OnEndOverlap);
	
	DoorTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("DoorTimeline"));
	
	OpeningSound = CreateDefaultSubobject<UAudioComponent>("OpeningSound");
	OpeningSound->SetupAttachment(RootComponent);

	InterpFunction.BindUFunction(this, FName("SlideDoor"));
	TimelineFinished.BindUFunction(this, FName("OnTimelineFinished"));
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	OpeningSound->Stop();
	if (DoorSlideCurve)
	{
		DoorTimeline->AddInterpFloat(DoorSlideCurve, InterpFunction);
		DoorTimeline->SetTimelineFinishedFunc(TimelineFinished);
	}
	
	InitialDoorLocation = DoorMeshComponent->GetRelativeLocation();
	TargetDoorLocation = InitialDoorLocation + FVector(150.f, 0.f, 0.f);
	
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	LockMeshComponent->SetMaterial(0, bIsUnlocked ? UnlockedMaterial : LockedMaterial);
}

void ADoor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bIsUnlocked && OtherActor->IsA(APlayerCharacter::StaticClass()))
		OpenDoor();
}

void ADoor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,int32 OtherBodyIndex)
{
	if (bIsUnlocked && OtherActor->IsA(APlayerCharacter::StaticClass()))
		CloseDoor();
}

void ADoor::SlideDoor(float Value)
{
	FVector NewLocation = InitialDoorLocation;
	NewLocation.X = FMath::Lerp(InitialDoorLocation.X, TargetDoorLocation.X, Value);
	
	DoorMeshComponent->SetRelativeLocation(NewLocation);
}

void ADoor::OpenDoor()
{
	if (!bIsOpen)
	{
		OpeningSound->Deactivate();
		OpeningSound->Activate();
		DoorTimeline->Play();
		bIsOpen = true;
	}
}

void ADoor::CloseDoor()
{
	if (bIsOpen)
	{
		OpeningSound->Deactivate();
		OpeningSound->Activate();
		DoorTimeline->Reverse();
		bIsOpen = false;
	}
}

void ADoor::Activate()
{
	bIsUnlocked = true;
}
void ADoor::OnTimelineFinished()
{
}

