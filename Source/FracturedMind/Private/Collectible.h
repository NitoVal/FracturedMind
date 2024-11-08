// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Collectible.generated.h"

UCLASS()
class ACollectible : public AActor
{
	GENERATED_BODY()
	
public:	
	ACollectible();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USceneComponent* DefaultSceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UStaticMeshComponent* CollectibleMeshComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Collectible")
	FDataTableRowHandle Collectible;
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
