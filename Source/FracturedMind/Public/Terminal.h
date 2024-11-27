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
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UWidgetComponent* MonitorWidgetComponent;
	
	UPROPERTY(EditAnywhere, Category = "Terminal | UI", meta = (EditCondition = "bIsInteractable", EditConditionHides))
	TSubclassOf<UWidgetCode> MonitorWidgetClass;

	UPROPERTY(EditAnywhere, Category = "Terminal | UI")
	TSubclassOf<UUserWidget> AccessGrantedWidgetClass;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Terminal | Puzzle", meta = (EditCondition = "bIsInteractable", EditConditionHides))
	FString MonitorPassword;
	
	UPROPERTY(EditAnywhere, Category="Terminal | Interaction")
	bool bIsInteractable;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="Terminal | Completion Activators")
	TArray<AActor*> Activators;

	void ShowMonitorUI();
	void CloseMonitorUI();
	void ActivateActivators();
	void Activate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	virtual void Interact() override;
	virtual bool IsInteractable() override;
	
private:
	UPROPERTY()
	UWidgetCode* MonitorWidget;

	UPROPERTY()
	UUserWidget* AccessGrantedWidget;
};
