// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PuzzleCompletionEventInterface.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

class UBoxComponent;
class UTimelineComponent;
class ADoorCoded;

UCLASS()
class FRACTUREDMIND_API ADoor : public AActor, public IPuzzleCompletionEventInterface
{
	GENERATED_BODY()
	
public:	
	ADoor();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USceneComponent* DefaultSceneRoot;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UStaticMeshComponent* DoorMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UStaticMeshComponent* LockMeshComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UBoxComponent* TriggerBox;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Components")
	UAudioComponent* OpeningSound;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UTimelineComponent* DoorTimeline;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Door")
	bool bIsUnlocked;
	
	FOnTimelineFloat InterpFunction{};
	FOnTimelineEvent TimelineFinished{};
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCurveFloat* DoorSlideCurve;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Door")
	UMaterialInstance* LockedMaterial;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Door")
	UMaterialInstance* UnlockedMaterial;

	virtual void Activate() override;
private:
	friend class ATerminal;
	bool bIsOpen;

	FVector InitialDoorLocation;
	FVector TargetDoorLocation;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UFUNCTION()
	void SlideDoor(float Value);
	
	UFUNCTION()
	void OpenDoor();

	UFUNCTION()
	void CloseDoor();

	void OnTimelineFinished();
};
