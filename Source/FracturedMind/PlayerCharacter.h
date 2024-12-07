// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h" 
#include "Private/Collectible.h"
#include "Private/CollectionWidget.h"
#include "Terminal.h"
#include "Sound/SoundBase.h"
#include "PlayerCharacter.generated.h"

class ACollectible;
class ATerminal;
class AItem;
class ABigItems;
class IInteractionInterface;
class UPauseWidget;
class UCollectionWidget;
class UPlayerWidget;
class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext; 
struct FInputActionValue;

UCLASS()
class FRACTUREDMIND_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Mesh, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Mesh1P;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USceneComponent* HandPosition;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USceneComponent* HandPositionBigItem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USceneComponent* InspectPosition;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* InspectMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* DropAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PlaceItemAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PauseAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* ExitInspectAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* RotateAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* CollectionAction;
public:
	// Sets default values for this character's properties
	APlayerCharacter();
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Player | UI")
	TSubclassOf<UUserWidget> PlayerWidgetClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Player | UI")
	TSubclassOf<UUserWidget> PauseWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Player | UI")
	TSubclassOf<UUserWidget> SettingsWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Player | UI")
	TSubclassOf<UCollectionWidget> CollectionWidgetClass;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Player | Item")
	AItem* Hand;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Player | BigItems")
	ABigItems* HandBigItem; 
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Player | Collectibles")
	TArray<ACollectible*> Collectibles;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player | Settings")
	float Sensitivity = 1.0f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Player | Pause")
	bool bCanOpenUI;
	
	UPlayerWidget* PlayerWidget;
	UCollectionWidget* CollectionWidget;
	UPauseWidget* PauseWidget;
	
	void SetSensitivity(float NewSensitivity);
    void PickupBigItem(ABigItems* BigItems);
	void PlaceBigItem(); 
	void Pickup(AItem* Item);
	void Pause();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundBase* UncomfortableSound;
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value); 
	void Interact();   
	void Drop();
	void EnterInspect();
	void ExitInspect();
	void RotateInspect(const FInputActionValue& Value);
	void ToggleCollection();
private:
	bool bIsInspecting;
	bool bIsPauseUIOpen;
	bool bIsCollectionOpen;
	TScriptInterface<IInteractionInterface> CurrentInteractable; 
	
	AActor* CurrentInspectObject;
	FRotator CurrentInspectRotation;
	ATerminal* TerminalReference;
	 
	void PerformLineTrace();
};
