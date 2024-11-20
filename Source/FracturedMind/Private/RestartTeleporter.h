// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "RestartTeleporter.generated.h"

UCLASS()
class ARestartTeleporter : public AActor
{
	GENERATED_BODY()

public:	
	ARestartTeleporter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USceneComponent* DefaultSceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UBoxComponent* TriggerBox;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="Teleporter")
	AActor* TeleportPosition;
protected:
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
