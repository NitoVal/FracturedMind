// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Blocker.generated.h"

class APlayerCharacter;
class UBoxComponent;

UCLASS()
class ABlocker : public AActor
{
	GENERATED_BODY()
	
public:	
	ABlocker();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USceneComponent* DefaultSceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UStaticMeshComponent* BlockerMeshComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	APlayerCharacter* PlayerCharacter;
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
