// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
  
#include "CoreMinimal.h"
#include "FracturedMind/InteractionInterface.h"
#include "GameFramework/Actor.h"
#include "Chair.generated.h"

UCLASS()
class FRACTUREDMIND_API AChair : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChair();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
    USceneComponent* DefaultSceneRoot;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
    UStaticMeshComponent* ChairComp; 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	virtual void Interact() override;
    virtual bool IsInteractable() override;

public:	
	// Called every frame


};
