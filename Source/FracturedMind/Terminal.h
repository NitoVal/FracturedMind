// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractionInterface.h"
#include "GameFramework/Actor.h"
#include "Terminal.generated.h"

class UWidgetComponent;

UENUM()
enum class EPuzzleType : int8
{
	PASSWORD UMETA(DisplayName = "Password"),
	LOCK UMETA(DisplayName = "Lock")
	
};
UCLASS()
class FRACTUREDMIND_API ATerminal : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
public:	
	ATerminal();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USceneComponent* DefaultSceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UStaticMeshComponent* TerminalMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UWidgetComponent* TerminalWidgetComponent;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="Terminal | Completion Activators", meta=(EditCondition = "bIsInteractable", EditConditionHides))
	TArray<AActor*> Activators;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="Terminal | Completion Activators", meta=(EditCondition = "bIsInteractable", EditConditionHides))
	EPuzzleType PuzzleType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Terminal | UI", meta=(EditCondition = "bIsInteractable", EditConditionHides))
	TSubclassOf<UUserWidget> TerminalWidgetClass;
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	virtual void Interact() override;
	virtual bool IsInteractable() override;
private:
	UPROPERTY(EditAnywhere, Category="Terminal | Interaction")
	bool bIsInteractable;

	UUserWidget* TerminalWidget;
};
