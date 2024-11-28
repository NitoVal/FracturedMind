// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NiagaraComponent.h"
#include "CoreMinimal.h"
#include "InteractionInterface.h"
#include "PuzzleCompletionEventInterface.h"
#include "GameFramework/Actor.h"
#include "Switch.generated.h"

class IPuzzleCompletionEventInterface;

UCLASS()
class FRACTUREDMIND_API ASwitch : public AActor, public IInteractionInterface, public IPuzzleCompletionEventInterface
{
	GENERATED_BODY()

public:	
	ASwitch();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USceneComponent* DefaultSceneRoot;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UStaticMeshComponent* SwitchBaseMeshComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UStaticMeshComponent* SwitchButtonMeshComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UAudioComponent* SwitchSFX;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UNiagaraComponent* SwitchVFX;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Switch | Materials")
	UMaterial* SwitchOnMaterial;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Switch | Materials")
	UMaterial* SwitchOffMaterial;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="Switch | Completion Activators")
	TArray<AActor*> Activators;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void Interact() override;
	virtual bool IsInteractable() override;
	virtual void Activate() override;
private:
	UPROPERTY(EditAnywhere, Category="Switch | Interactable")
	bool bCanBePressed;
};
