// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FracturedMind/InteractionInterface.h"
#include "GameFramework/Actor.h"
#include "BigItems.generated.h" 

UCLASS()
class ABigItems : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABigItems();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override; 
	virtual void Tick(float DeltaTime) override;

	virtual void Interact() override;
	virtual bool IsInteractable() override; 
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UStaticMeshComponent* BigItemComp;  
};
