#pragma once

#include "CoreMinimal.h"
#include "FracturedMind/Door.h"
#include "WidgetCode.h"
#include "FracturedMind/InteractionInterface.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"
#include "Terminal.generated.h"

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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Code")
	TArray<int32> Code; 

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Code")
	TArray<int32> CurrentCodeInput;

	UFUNCTION(BlueprintCallable, Category = "Code")
	void EnterCode(int32 CodeDigit);

	UFUNCTION(BlueprintCallable, Category = "Code")
	void CheckCode();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door Reference")
	ADoor* LinkedDoor;

	virtual void Interact() override;
	virtual bool IsInteractable() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Player | UI")
	TSubclassOf<UUserWidget> WidgetCodeClass;

	UWidgetCode* WidgetCode;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
