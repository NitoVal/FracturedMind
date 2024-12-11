// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractionInterface.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class FRACTUREDMIND_API AItem : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USceneComponent* DefaultSceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UStaticMeshComponent* ItemMeshComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item | Hold Rotation")
	FRotator HoldRotation;

	FTransform OriginalTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Properties")
	bool bIsHammer;

	bool IsHammer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	virtual void Interact() override;
	virtual bool IsInteractable() override;
};
