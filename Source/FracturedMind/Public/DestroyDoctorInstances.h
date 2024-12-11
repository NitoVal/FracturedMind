// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "DestroyDoctorInstances.generated.h"

UCLASS()
class FRACTUREDMIND_API ADestroyDoctorInstances : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADestroyDoctorInstances();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* TriggerBox;
 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PNJ Instance")
	AActor* DoctorInstanceToDestroy;
 
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
						UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
						bool bFromSweep, const FHitResult& SweepResult); 
};
