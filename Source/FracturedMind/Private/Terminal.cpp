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

	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClassFinder(TEXT("FracturedMind/WidgetCode"));
	if (WidgetClassFinder.Succeeded())
	{
		WidgetCodeClass = WidgetClassFinder.Class;
	}
}

// Called when the game starts or when spawned
void ATerminal::BeginPlay()
{
	Super::BeginPlay(); 
}

// Called every frame
void ATerminal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATerminal::Interact()
{
	if (WidgetCode && WidgetCode->GetCorrectCode())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Le bon code a déjà été entré."));
		return; 
	}
	if (WidgetCodeClass)   
	{ 
		if (UUserWidget* UserWidget = CreateWidget<UUserWidget>(GetWorld(), WidgetCodeClass))  
		{
			WidgetCode = Cast<UWidgetCode>(UserWidget);
			if (WidgetCode) 
			{ 
				WidgetCode->SetOwningTerminal(this);
				WidgetCode->AddToViewport(); 
				APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
				if (PlayerController)
				{
					PlayerController->bShowMouseCursor = true;   
					PlayerController->SetInputMode(FInputModeUIOnly());
				}
			} 
		}
	} 
} 

bool ATerminal::IsInteractable()
{
	return true;
} 

void ATerminal::CheckCode()
{ 
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	
	if (PlayerController)
	{
		PlayerController->bShowMouseCursor = false;
		PlayerController->SetInputMode(FInputModeGameOnly());

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Jeu remis"));

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
}
 