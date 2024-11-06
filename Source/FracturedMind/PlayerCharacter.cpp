// Fill out your copyright notice in the Description page of Project Settings.
#include "PlayerCharacter.h"

#include "PlayerWidget.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "InteractionInterface.h"
#include "Item.h"
#include "Private/BigItems.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	HandPosition = CreateDefaultSubobject<USceneComponent>(TEXT("HandPosition"));
	HandPosition->SetupAttachment(FirstPersonCameraComponent);

	HandPositionBigItem = CreateDefaultSubobject<USceneComponent>(TEXT("HandPositionBigItem"));
	HandPositionBigItem->SetupAttachment(FirstPersonCameraComponent);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* PlayerController = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
	PlayerController->SetInputMode(FInputModeGameOnly());
	PlayerController->bShowMouseCursor = false;
	
	if (PlayerWidgetClass)
	{
		UUserWidget* UserWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerWidgetClass);
		PlayerWidget = Cast<UPlayerWidget>(UserWidget);
		PlayerWidget->AddToViewport();
	}
	if (PauseWidgetClass)
	{
		UUserWidget* UserWidget = CreateWidget<UUserWidget>(GetWorld(), PauseWidgetClass);
		PauseWidget = UserWidget;
		PauseWidget->AddToViewport();
		PauseWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	PerformLineTrace();
	if (Hand)
	{
		HandPosition->SetRelativeRotation(Hand->HoldRotation);
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (const APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
	
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);

		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Interact);
		EnhancedInputComponent->BindAction(DropAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Drop);
		EnhancedInputComponent->BindAction(PlaceItemAction, ETriggerEvent::Triggered, this, &APlayerCharacter::PlaceBigItem);
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Pause);
	}
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APlayerCharacter::Interact()
{
	if (CurrentInteractable && CurrentInteractable->IsInteractable())
	{
		CurrentInteractable->Interact();
		PlayerWidget->SetInteractPromptVisibility(false);
	}
}

void APlayerCharacter::Pause()
{
	//Retrieve player controller in the world
	APlayerController* PlayerController = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
	if (PlayerController)
	{
		//Check if the game is paused
		if (PlayerController->IsPaused())
		{
			PlayerController->SetPause(false);
			PlayerController->SetInputMode(FInputModeGameOnly());
			PlayerController->bShowMouseCursor = false;
			
			PauseWidget->SetVisibility(ESlateVisibility::Collapsed);
			PlayerWidget->SetVisibility(ESlateVisibility::Visible);
		}
		else //The game is not paused
		{
			PlayerController->SetPause(true);
			FInputModeGameAndUI InputMode;
			InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			PlayerController->SetInputMode(InputMode);
			PlayerController->bShowMouseCursor = true;
			
			PauseWidget->SetVisibility(ESlateVisibility::Visible);
			PlayerWidget->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void APlayerCharacter::Pickup(AItem* Item)
{
	//Check if the player has no item
	if (!Hand && !HandBigItem)
	{
		Hand = Item;
		Hand->AttachToComponent(HandPosition,FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		Hand->SetActorLocation(HandPosition->GetComponentLocation());
	}
}

void APlayerCharacter::PickupBigItem(ABigItems* BigItems) // Called in Class BigItems so the called scene in the character bp is different
{
	//Check if the player has no item  
	if (!Hand && !HandBigItem)
	{
		HandBigItem = BigItems;
		HandBigItem->AttachToComponent(HandPositionBigItem,FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		HandBigItem->SetActorLocation(HandPositionBigItem->GetComponentLocation());
	}
}

void APlayerCharacter::PlaceBigItem()
{
	//Check if the player have an item
	if (!Hand && HandBigItem)
	{
		FVector Start = FirstPersonCameraComponent->GetComponentLocation();
		FVector ForwardVector = FirstPersonCameraComponent->GetForwardVector();
		FVector PlaceLocation = Start + (ForwardVector * 200.f);
		
		HandBigItem->SetActorLocation(PlaceLocation);
		
		HandBigItem->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		HandBigItem->SetActorEnableCollision(true); 
		HandBigItem = nullptr;  
	}
}

void APlayerCharacter::Drop()
{
	//Check if the player has an item
	if (Hand)
	{
		Hand->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Hand->SetActorEnableCollision(true);
		Hand = nullptr;
	}
}

void APlayerCharacter::PerformLineTrace()
{
	FHitResult Result;
	const FVector Start = GetFirstPersonCameraComponent()->GetComponentLocation();
	const FVector End = Start + FirstPersonCameraComponent->GetForwardVector() * 200.f;

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByObjectType(Result,Start, End, ObjectQueryParams, QueryParams) && IsValid(Result.GetActor()))
	{
		if (Result.GetActor()->Implements<UInteractionInterface>())
		{
			CurrentInteractable = Result.GetActor();
			if (CurrentInteractable->IsInteractable())
				PlayerWidget->SetInteractPromptVisibility(true);
		}
	}
	else
	{
		CurrentInteractable = nullptr;
		PlayerWidget->SetInteractPromptVisibility(false);
	}
}

