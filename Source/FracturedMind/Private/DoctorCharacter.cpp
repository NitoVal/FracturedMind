// Fill out your copyright notice in the Description page of Project Settings.


#include "DoctorCharacter.h"
#include "Components/BoxComponent.h"

// Sets default values
ADoctorCharacter::ADoctorCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(RootComponent);
	TriggerBox->SetBoxExtent(FVector(200.f, 200.f, 100.f));
	TriggerBox->SetCollisionProfileName(TEXT("Trigger"));
 
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ADoctorCharacter::OnOverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ADoctorCharacter::OnOverlapEnd);

}

// Called when the game starts or when spawned
void ADoctorCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (!AM_IdleAnimation || SpeakingAnimations.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Idle or Speaking Animations not set on %s"), *GetName());
	} 
}

// Called every frame
void ADoctorCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADoctorCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ADoctorCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
									UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
									bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		UE_LOG(LogTemp, Log, TEXT("Player entered the trigger zone"));

		// Start speaking
		StartSpeaking();
	}
}

void ADoctorCharacter::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
								  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor != this)
	{
		UE_LOG(LogTemp, Log, TEXT("Player left the trigger zone"));

		// Stop speaking
		StopSpeaking();
	}
}

void ADoctorCharacter::StartSpeaking()
{
	GetWorldTimerManager().SetTimer(SpeakingTimerHandle, this, &ADoctorCharacter::PlayRandomSpeakingAnimation, 3.f, true);
	PlayRandomSpeakingAnimation();  
}

void ADoctorCharacter::StopSpeaking()
{
	GetWorldTimerManager().ClearTimer(SpeakingTimerHandle);

	// Return to idle animation
	if (AM_IdleAnimation)
	{
		PlayAnimMontage(AM_IdleAnimation);
	}
}

void ADoctorCharacter::PlayRandomSpeakingAnimation()
{
	if (SpeakingAnimations.Num() > 0)
	{
		int32 RandomIndex = FMath::RandRange(0, SpeakingAnimations.Num() - 1);
		PlayAnimMontage(SpeakingAnimations[RandomIndex]);
	}
}
