// Fill out your copyright notice in the Description page of Project Settings.


#include "DestroyDoctorInstances.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h" 
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADestroyDoctorInstances::ADestroyDoctorInstances()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(RootComponent);
	TriggerBox->SetBoxExtent(FVector(150.f, 150.f, 100.f));  
	TriggerBox->SetCollisionProfileName(TEXT("Trigger"));
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ADestroyDoctorInstances::OnOverlapBegin);
}

// Called when the game starts or when spawned
void ADestroyDoctorInstances::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADestroyDoctorInstances::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADestroyDoctorInstances::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
											 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
											 bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
 
	if (OtherActor && Cast<ACharacter>(OtherActor) == PlayerCharacter && DoctorInstanceToDestroy)
	{ 
		DoctorInstanceToDestroy->Destroy();   
	}
}
