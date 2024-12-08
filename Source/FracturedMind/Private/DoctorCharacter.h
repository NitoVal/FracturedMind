// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FracturedMind/DialogueData.h"
#include "DoctorCharacter.generated.h" 

class UAnimMontage;
class UBoxComponent; 

UCLASS()
class ADoctorCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADoctorCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void LookAtPlayer(AActor* PlayerActor);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	UDataTable* DialogueDataTable;   
 
	FDialogueData* FindDialogueForActor(const FVector& ActorPosition);

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* TriggerBox; 
 
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> AM_IdleAnimation;

	UPROPERTY(EditAnywhere)
	TArray<UAnimMontage*> SpeakingAnimations;

	FTimerHandle SpeakingTimerHandle; 
	FTimerHandle SpeakingStopTimerHandle; 
 
	void StartSpeaking(FDialogueData* DialogueData);
	void StopSpeaking();
	void PlayRandomSpeakingAnimation();
 
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
						UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, 
						const FHitResult& SweepResult);
 
}; 
