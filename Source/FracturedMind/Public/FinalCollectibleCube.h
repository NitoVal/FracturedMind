// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FracturedMind/InteractionInterface.h" 
#include "Components/BoxComponent.h"
#include "FinalCollectibleCube.generated.h"

UCLASS()
class FRACTUREDMIND_API AFinalCollectibleCube : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFinalCollectibleCube();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USceneComponent* DefaultSceneRoot;
	
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* TriggerBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components")
	UStaticMeshComponent* CubeMesh; 
	
	virtual void Interact() override;
	virtual bool IsInteractable() override;

};
