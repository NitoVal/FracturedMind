#include "FracturedMind/Public/Terminal.h"

#include "Blueprint/UserWidget.h"
#include "FracturedMind/Door.h"
#include "Components/InputComponent.h"

// Sets default values
ATerminal::ATerminal()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;

	TerminalMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TerminalMeshComponent"));
	TerminalMeshComponent->SetupAttachment(RootComponent);

	ClavierMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ClavierMeshComponent"));
	ClavierMeshComponent->SetupAttachment(RootComponent);

	ScreenMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ScreenMeshComponent"));
	ScreenMeshComponent->SetupAttachment(RootComponent);

	MonitorWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("MonitorWidget"));
	MonitorWidgetComponent->SetupAttachment(ScreenMeshComponent);
	MonitorWidgetComponent->SetWidgetSpace(EWidgetSpace::World);
	bIsInteractable = true;
}

// Called when the game starts or when spawned
void ATerminal::BeginPlay()
{
	Super::BeginPlay();
	if (MonitorWidgetClass)
		MonitorWidgetComponent->SetWidgetClass(MonitorWidgetClass);
}

// Called every frame
void ATerminal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATerminal::Interact()
{
	ShowMonitorUI();
} 
void ATerminal::ShowMonitorUI()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController && MonitorWidgetClass != nullptr)
	{
		if (MonitorWidget == nullptr)
		{
			MonitorWidget = CreateWidget<UWidgetCode>(PlayerController, MonitorWidgetClass);

			if (MonitorWidget)
			{
				MonitorWidget->OwningTerminal = this;
				MonitorWidget->AddToViewport();
			
				PlayerController->bShowMouseCursor = true;
				PlayerController->SetInputMode(FInputModeUIOnly());
			}
		}
	}
}

void ATerminal::CloseMonitorUI()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController && MonitorWidget != nullptr)
	{
		MonitorWidget->RemoveFromParent();
		MonitorWidget = nullptr;
		
		PlayerController->bShowMouseCursor = false;
		PlayerController->SetInputMode(FInputModeGameOnly());
	}
}

void ATerminal::ActivateActivators()
{
	for (AActor* Actor : Activators)
	{
		//Check if the actor has the UPuzzleCompletionEventInterface
		if (Actor && Actor->GetClass()->ImplementsInterface(UPuzzleCompletionEventInterface::StaticClass()))
		{
			IPuzzleCompletionEventInterface* InterfaceInstance = Cast<IPuzzleCompletionEventInterface>(Actor);
			if (InterfaceInstance)
				InterfaceInstance->Activate();
		}
	}
}

void ATerminal::Activate()
{
	MonitorWidgetComponent->SetWidgetClass(AccessGrantedWidgetClass);
}

bool ATerminal::IsInteractable()
{
	return bIsInteractable;
}
 