// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractionInterface.h"
#include "GameFramework/Actor.h"
#include "Breakable.generated.h"

UCLASS()
class FRACTUREDMIND_API ABreakable : public AActor, public IInteractionInterface
{
	GENERATED_BODY()


public:	
	ABreakable();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USceneComponent* DefaultSceneRoot;
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void Interact() override;
	virtual bool IsInteractable() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Breakable")
	FString RequiredTag;
};
