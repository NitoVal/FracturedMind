// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractionInterface.h"
#include "GameFramework/Actor.h"
#include "Switch.generated.h"

class IPuzzleCompletionEventInterface;

UCLASS()
class FRACTUREDMIND_API ASwitch : public AActor, public IInteractionInterface
{
	GENERATED_BODY()


public:	
	ASwitch();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USceneComponent* DefaultSceneRoot;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UStaticMeshComponent* SwitchMeshComponent;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="Completion Activators")
	TArray<AActor*> Activators;
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void Interact() override;
	virtual bool IsInteractable() override;
private:
	UPROPERTY(EditAnywhere, Category="Button")
	bool bCanBePressed;
};
