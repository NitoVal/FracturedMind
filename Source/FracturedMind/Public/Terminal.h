#pragma once

#include "CoreMinimal.h"
#include "FracturedMind/Door.h"
#include "WidgetCode.h"
#include "FracturedMind/InteractionInterface.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"
#include "Terminal.generated.h" 

class IPuzzleCompletionEventInterface;

UCLASS()
class FRACTUREDMIND_API ATerminal : public AActor, public IInteractionInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATerminal();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USceneComponent* DefaultSceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UStaticMeshComponent* TerminalMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UStaticMeshComponent* ClavierMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UStaticMeshComponent* ScreenMeshComponent;

	UFUNCTION(BlueprintCallable, Category = "Code")
	void CheckCode();
	
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="Terminal | Completion Activators")
	TArray<AActor*> Activators;
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	virtual void Interact() override;
	virtual bool IsInteractable() override; 

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UUserWidget> WidgetCodeClass;
	
	UWidgetCode* WidgetCode; 
	
};
