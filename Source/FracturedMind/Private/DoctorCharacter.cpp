// Fill out your copyright notice in the Description page of Project Settings.


#include "DoctorCharacter.h"
#include "Components/BoxComponent.h" 
#include "Sound/SoundBase.h" 
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h" 
#include "Components/BoxComponent.h"
#include "FracturedMind/PlayerCharacter.h"

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
}

// Called when the game starts or when spawned
void ADoctorCharacter::BeginPlay()
{
	Super::BeginPlay(); 
}

// Called every frame
void ADoctorCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AActor* PlayerActor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	LookAtPlayer(PlayerActor);
}

// Called to bind functionality to input
void ADoctorCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent); 
} 

FDialogueData* ADoctorCharacter::FindDialogueForActor(const FVector& ActorPosition)
{
	static const FString ContextString(TEXT("Dialogue Context"));
	TArray<FName> RowNames = DialogueDataTable->GetRowNames();

	for (const FName& RowName : RowNames)
	{
		FDialogueData* DialogueData = DialogueDataTable->FindRow<FDialogueData>(RowName, ContextString);
		if (DialogueData)
		{
			for (const FVector& ValidPosition : DialogueData->ValidPositions)
			{
				if (ActorPosition.Equals(ValidPosition, 300.f))  
				{
					return DialogueData;
				}
			}
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("No dialogue found for position: %s"), *ActorPosition.ToString());
	return nullptr;
}

void ADoctorCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
									   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
									   bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor); 
		if ((OtherActor && Cast<ACharacter>(OtherActor) == PlayerCharacter)) 
		{
			if (TriggerBox && TriggerBox->IsOverlappingActor(PlayerCharacter))
			{  
				FVector ActorPosition = PlayerCharacter->GetActorLocation();
				FDialogueData* DialogueData = FindDialogueForActor(ActorPosition); 

				if (DialogueData)
				{ 
					for (const FVector& ValidPosition : DialogueData->ValidPositions)
					{ 
						if (ActorPosition.Equals(ValidPosition, 300.f))   
						{
							StartSpeaking(DialogueData);
							TriggerBox->DestroyComponent();
							return;  
						}
					}
				}
			}
		}
	}
}
 
void ADoctorCharacter::StartSpeaking(FDialogueData* DialogueData)
{
	if (DialogueData)
	{  
		if (DialogueData->AudioFile)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), DialogueData->AudioFile);
		}
		float StopSpeakingDelay = 17.0f;  
		GetWorldTimerManager().SetTimer(SpeakingStopTimerHandle, this, &ADoctorCharacter::StopSpeaking, StopSpeakingDelay, false);
		
		GetWorldTimerManager().SetTimer(SpeakingTimerHandle, this, &ADoctorCharacter::PlayRandomSpeakingAnimation, 3.f, true);
		PlayRandomSpeakingAnimation();  
	}  
}

void ADoctorCharacter::LookAtPlayer(AActor* PlayerActor)
{
	if (!PlayerActor)
	{
		return;
	}
 
	FVector NPCPosition = GetActorLocation();
	FVector PlayerPosition = PlayerActor->GetActorLocation();
	
	FVector DirectionToPlayer = (PlayerPosition - NPCPosition).GetSafeNormal();
	FRotator LookAtRotation = FRotationMatrix::MakeFromX(PlayerPosition - NPCPosition).Rotator();

	SetActorRotation(FRotator(0.f, LookAtRotation.Yaw, 0.f));
}

void ADoctorCharacter::StopSpeaking()
{
	GetWorldTimerManager().ClearTimer(SpeakingTimerHandle);
	GetWorldTimerManager().ClearTimer(SpeakingStopTimerHandle);
	
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